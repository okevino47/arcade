/*
** EPITECH PROJECT, 2018
** Core.hpp
** File description:
** header
*/

#ifndef	CORE_HPP_
# define	CORE_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Menu.hpp"
#include "macro.hpp"
#include "IGame.hpp"
#include "IGraphical.hpp"

class Core
{
public:
	Core();
	~Core();

	void	getGraphicals(std::string const &currentLib);
	void	getGames();
	int	arcadeLoop();

private:
	int		getInstanceOfGraphical(std::string const &file);
	int		getInstanceOfGame(std::string const &file);
	eventStatus	runMenu();
	std::string	defineString();
	eventStatus	prevMenuPage();
	eventStatus	nextMenuPage();
	eventStatus	prevName();
	eventStatus	nextName();
	eventStatus	runGame();
	void		displayUI();
	void		displayMap();
	void		movePlayer();
	eventStatus	detectEvent();
	eventStatus	quitProgram();
	eventStatus	returnToMenu();
	eventStatus	canMoveUp();
	eventStatus	canMoveLeft();
	eventStatus	canMoveDown();
	eventStatus	canMoveRight();
	eventStatus	restartGame();
	eventStatus	getPrevLib();
	eventStatus	getNextGame();
	eventStatus	getNextLib();
	eventStatus	getPrevGame();

private:
	Menu						_menu;
	std::vector<std::string>			_lnames;
	std::vector<IGraphical *(*)(void)>		_libs;
	std::vector<std::string>			_gnames;
	std::vector<IGame *(*)(void)>			_games;
	int						_indexLib;
	int						_indexGame;
	std::vector<void (Menu::*)(IGraphical *, std::string)>	_pages;
	int						_indexPage;
	IGraphical					*_currentLib;
	IGame						*_currentGame;
	std::string					_playerName;
	direction					_direction;
	int						_timer;
};

#endif	/* CORE_HPP_ */
