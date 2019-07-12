/*
** EPITECH PROJECT, 2018
** Core.cpp
** File description:
** function
*/

#include "Core.hpp"

#include <dlfcn.h>
#include <dirent.h>
#include <sys/types.h>

/*!
* Constructor of the class "Core"
*/

Core::Core():
_menu(Menu()),
_indexLib(0),
_indexGame(-1),
_indexPage(0),
_currentGame(nullptr),
_playerName("___"),
_direction(NONE),
_timer(0)
{
	_pages.push_back(&Menu::runPage1);
	_pages.push_back(&Menu::runPage2);
	_pages.push_back(&Menu::runPage3);
	_pages.push_back(&Menu::runPage4);
	_pages.push_back(&Menu::runPage5);
}

/*!
* Destructor of the class "Core"
*/

Core::~Core()
{}

/*!
* Get all Graphical Librarie's Classes in the lib/ folder
* @param [in] currentLib
*/

void	Core::getGraphicals(std::string const &currentLib)
{
	DIR		*dp;
	struct dirent	*dirp;

	if (getInstanceOfGraphical(currentLib) == ERROR)
		throw std::invalid_argument("USAGE: ./arcade lib_path");
	if ((dp = opendir("lib/")) == NULL)
		throw std::invalid_argument("Can't open ./lib");
	while ((dirp = readdir(dp)) != NULL) {
		std::string	file = dirp->d_name;
		if (currentLib.find(file) == std::string::npos)
			getInstanceOfGraphical("./lib/" + file);
	}
	closedir(dp);
}

/*!
* Function that open a shared library, get the symbol of the
* "getInstance" function and push it in _libs vector.
* @param [in] file
* @return "ERROR" if an error occured with ldl library
*	  "SUCCES" if no ldl library error
*/

int	Core::getInstanceOfGraphical(std::string const &file)
{
	void		*handle;
	IGraphical	*(*getInstance)(void);

	if (file.find("lib_arcade_") == std::string::npos
		|| file.find(".so") == std::string::npos)
		return ERROR;
	if ((handle = dlopen(file.c_str(), RTLD_LAZY)) == NULL)
		return ERROR;
	getInstance = (IGraphical *(*)(void)) dlsym(handle, "getInstance");
	if (getInstance == NULL) {
		dlclose(handle);
		return ERROR;
	}
	_libs.push_back(getInstance);
	size_t	start = file[0] == '.' ? 17 : 15;
	_lnames.push_back(file.substr(start, file.size() - start - 3));
	return SUCCES;
}

/*!
* Get all Game Librarie's Classes in the games/ folder
*/

void	Core::getGames()
{
	DIR		*dp;
	struct dirent	*dirp;

	if ((dp = opendir("games/")) == NULL)
		throw std::invalid_argument("Can't open ./games");
	while ((dirp = readdir(dp)) != NULL) {
		std::string	file = dirp->d_name;
		getInstanceOfGame("./games/" + file);
	}
	closedir(dp);
	if (_games.size() == 0)
		throw std::invalid_argument("No game to play");
}

/*!
* Function that open a shared library, get the symbol of the
* "getInstance" function and push that function in _games
* vector.
* @param [in] file
* @return "ERROR" if an error occured with ldl library
*	  "SUCCES" if no ldl library error
*/

int	Core::getInstanceOfGame(std::string const &file)
{
	void		*handle;
	IGame	*(*getInstance)(void);

	if (file.find("lib_arcade_") == std::string::npos
		|| file.find(".so") == std::string::npos)
		return ERROR;
	if ((handle = dlopen(file.c_str(), RTLD_LAZY)) == NULL)
		return ERROR;
	getInstance = (IGame *(*)(void)) dlsym(handle, "getInstance");
	if (getInstance == NULL) {
		dlclose(handle);
		return ERROR;
	}
	_games.push_back(getInstance);
	_gnames.push_back(file.substr(19, file.size() - 22));
	return SUCCES;
}

/*!
*
* @return "SUCCES" if the program ends correctly
*	  "ERROR" if an error occured
*/

int	Core::arcadeLoop()
{
	_currentLib = _libs[_indexLib]();
	while (1) {
		if (_indexGame == -1) {
			_playerName.assign("___");
			_indexGame++;
			_indexPage = 0;
			if (runMenu() == QUIT)
				break;
		} else {
			_currentGame = _games[_indexGame]();
			if (runGame() == QUIT)
				break;
			delete _currentGame;
			_currentGame = nullptr;
		}
	}
	return SUCCES;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventStatus	Core::runMenu()
{
	std::unordered_map<eventKey,
			eventStatus (Core::*)(void)>	events = {
		{ESCAPE, &Core::quitProgram}, {BACKSPACE, &Core::prevMenuPage},
		{ENTER, &Core::nextMenuPage}, {LEFT, &Core::prevName},
		{RIGHT, &Core::nextName}
	};

	while (1) {
		_menu.displayUI(_currentLib, _lnames[_indexLib]);
		(_menu.*_pages[_indexPage])(_currentLib, defineString());
		std::size_t	found = _playerName.find('_');
		if (_indexPage == 1 && found != std::string::npos)
			_playerName[found] = _currentLib->waitForCharKey();
		else {
			eventStatus	ret;
			ret = (this->*events[_currentLib->waitForMenuKey()])();
			if (ret == QUIT || ret == BREAK)
				return ret;
		}
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

std::string	Core::defineString()
{
	switch (_indexPage) {
		case 1:
			return _playerName;
		case 2:
			return _lnames[_indexLib];
		case 3:
			return _gnames[_indexGame];
		case 4:
			return _gnames[_indexGame];
		default:
			return _lnames[_indexLib];
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventStatus	Core::prevMenuPage()
{
	if (_indexPage != 0)
		_indexPage--;
	if (_indexPage < 3) {
		_playerName.assign("___");
	}
	return NOEVENT;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventStatus	Core::nextMenuPage()
{
	if ((size_t) _indexPage == _pages.size() - 1) {
		_indexPage = 0;
		return BREAK;
	}
	_indexPage++;
	return NOEVENT;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventStatus	Core::prevName()
{
	if (_indexPage == 2) {
		delete	_currentLib;
		_indexLib = _indexLib == 0 ? _libs.size() - 1 : _indexLib - 1;
		_currentLib = _libs[_indexLib]();
	} else if (_indexPage == 3) {
		_indexGame = _indexGame == 0 ?
			_games.size() - 1 : _indexGame - 1;
	}
	return NOEVENT;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventStatus	Core::nextName()
{
	if (_indexPage == 2) {
		delete	_currentLib;
		_indexLib = (_indexLib + 1) % _libs.size();
		_currentLib = _libs[_indexLib]();
	} else if (_indexPage == 3) {
		_indexGame = (_indexGame + 1) % _games.size();
	}
	return NOEVENT;
}

/*!
*
* @return <return_description>
* @details <details>
*/

eventStatus	Core::runGame()
{
	displayUI();
	displayMap();
	while (1 && !_currentGame->getEnd()) {
		eventStatus ret = detectEvent();
		if (ret == BREAK || ret == QUIT)
			return ret;
		movePlayer();
		displayUI();
		displayMap();
	}
	return returnToMenu();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Core::displayUI()
{
	std::string	tmp(std::to_string(_timer / 1000));
	std::string	help("Escape: quit - Backspace: menu\
 - LEFT: previous game - RIGHT: next game - UP: previous lib\
 - DOWN: next lib - R: restart game - ZQSD: move");

	_currentLib->clearWindow();
	_currentLib->displayText(std::make_pair(_lnames[_indexLib].size() * 15,
	 	15), _lnames[_indexLib], "white", 15);
	_currentLib->displayText(std::make_pair(WIN_WIDTH / 2, 100),
		_gnames[_indexGame], "orange", 100);
	_currentLib->displayText(std::make_pair(WIN_WIDTH / 2,
		WIN_HEIGHT - 100), help, "blue", 12);
	_currentLib->displayText(std::make_pair((tmp.size() + 6) * 30,
		WIN_HEIGHT / 2), "Time: " + tmp, "white", 30);
}

/*!
* Display the map of the game entity per entity.
*/

void	Core::displayMap()
{
	std::vector<std::vector<Entity>> const	&map = _currentGame->getMap();
	int const	size = _currentGame->getSize();

	for (size_t y = 0; y < map.size(); y++)
		for (size_t x = 0; x < map[y].size(); x++)
			_currentLib->displaySquare(&map[y][x], size,
				std::make_pair(map[0].size(), map.size()));
	_currentLib->updateScreen();
}

/*!
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
*/

void	Core::movePlayer()
{
	std::unordered_map<direction, void (IGame::*)(void)>	moves = {
		{UPDIR, &IGame::moveUp},
		{LEFTDIR, &IGame::moveLeft},
		{DOWNDIR, &IGame::moveDown},
		{RIGHTDIR, &IGame::moveRight}
	};

	if (_direction == NONE)
		return ;
	int	currentTime = _currentLib->getTimer();
	if (currentTime - _timer > _currentGame->getSpeed()) {
		(_currentGame->*moves[_direction])();
		_timer = currentTime;
	}
}

/*!
* Detect if an event occured and return which one.
* @return "BREAK" or "QUIT" or a direction
*	  ("LEFT", "RIGHT", ...) or "SUCCES"
*/

eventStatus	Core::detectEvent()
{
	std::unordered_map<eventKey,
				eventStatus (Core::*)(void)>	events = {
		{ESCAPE, &Core::quitProgram},
		{BACKSPACE, &Core::returnToMenu},
		{Z, &Core::canMoveUp},
		{Q, &Core::canMoveLeft},
		{S, &Core::canMoveDown},
		{D, &Core::canMoveRight},
		{R, &Core::restartGame},
		{UP, &Core::getPrevLib},
		{RIGHT, &Core::getNextGame},
		{DOWN, &Core::getNextLib},
		{LEFT, &Core::getPrevGame}
	};
	eventKey	key = _currentLib->getKeyPressed();

	if (key == NOKEY)
		return NOEVENT;
	return (this->*events[key])();
}

/*!
* Delete the insatance of IGame and IGraphical class.
* @return "QUIT" to quit the game loop and the arcade one
*/

eventStatus	Core::quitProgram()
{
	if (_currentGame)
		delete _currentGame;
	delete _currentLib;
	return QUIT;
}

/*!
* Set the index of the game to -1 to get the menu.
* @return "BREAK" to quit the game loop
*/

eventStatus	Core::returnToMenu()
{
	_currentLib->clearWindow();
	_currentLib->updateScreen();
	_indexGame = -1;
	_direction = NONE;
	_timer = 0;
	return BREAK;
}

/*!
* Call the member function of the game to check if
* the player can go up.
* @return "NOEVENT" if the player can't go up
*	  "CHANGEDIR" if he can
*/

eventStatus	Core::canMoveUp()
{
	if (_currentGame->isMoveAvailable(UPDIR) == SUCCES) {
		_direction = UPDIR;
		return CHANGEDIR;
	}
	return NOEVENT;
}

/*!
* Call the member function of the game to check if
* the player can go left.
* @return "NOEVENT" if the player can't go left
*	  "CHANGEDIR" if he can
*/

eventStatus	Core::canMoveLeft()
{
	if (_currentGame->isMoveAvailable(LEFTDIR) == SUCCES) {
		_direction = LEFTDIR;
		return CHANGEDIR;
	}
	return NOEVENT;
}

/*!
* Call the member function of the game to check if
* the player can go down.
* @return "NOEVENT" if the player can't go down
*	  "CHANGEDIR" if he can
*/

eventStatus	Core::canMoveDown()
{
	if (_currentGame->isMoveAvailable(DOWNDIR) == SUCCES) {
		_direction = DOWNDIR;
		return CHANGEDIR;
	}
	return NOEVENT;
}

/*!
* Call the member function of the game to check if
* the player can go right.
* @return "NOEVENT" if the player can't go right
*	  "CHANGEDIR" if he can
*/

eventStatus	Core::canMoveRight()
{
	if (_currentGame->isMoveAvailable(RIGHTDIR) == SUCCES) {
		_direction = RIGHTDIR;
		return CHANGEDIR;
	}
	return NOEVENT;
}

/*!
* Return "BREAK" without changing any value of index.
* @return "BREAK" to quit the game loop
*/

eventStatus	Core::restartGame()
{
	_currentLib->clearWindow();
	_currentLib->updateScreen();
	_direction = NONE;
	_timer = 0;
	_currentLib->resetTimer();
	return BREAK;
}

/*!
* Update the index of the current lib to get the
* previous one.
* @return "NOEVENT" to quit the game loop
*/

eventStatus	Core::getPrevLib()
{
	delete _currentLib;
	_indexLib = _indexLib == 0 ? _libs.size() - 1 : _indexLib - 1;
	_currentLib = _libs[_indexLib]();
	return NOEVENT;
}

/*!
* Update the index of the current game to get the
* next one.
* @return "BREAK" to quit the game loop
*/

eventStatus	Core::getNextGame()
{
	_indexGame = (_indexGame + 1) % _games.size();
	_currentLib->clearWindow();
	_currentLib->updateScreen();
	_direction = NONE;
	_timer = 0;
	_currentLib->resetTimer();
	return BREAK;
}

/*!
* Update the index of the current lib to get the
* next one.
* @return "NOEVENT" to quit the game loop
*/

eventStatus	Core::getNextLib()
{
	delete _currentLib;
	_indexLib = (_indexLib + 1) % _libs.size();
	_currentLib = _libs[_indexLib]();
	return NOEVENT;
}

/*!
* Update the index of the current game to get the
* previous one.
* @return "BREAK" to quit the game loop
*/

eventStatus	Core::getPrevGame()
{
	_indexGame = _indexGame == 0 ? _games.size() - 1 : _indexGame - 1;
	_currentLib->clearWindow();
	_currentLib->updateScreen();
	_direction = NONE;
	_timer = 0;
	_currentLib->resetTimer();
	return BREAK;
}
