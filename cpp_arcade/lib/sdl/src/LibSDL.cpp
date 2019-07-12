/*
** EPITECH PROJECT, 2018
** LibSDL.cpp
** File description:
** function
*/

#include "LibSDL.hpp"

/*!
* Constructor of LibSDL's class.
* Start of the SDL library by charging the video
* and joystick systems and then charge the window.
*/

LibSDL::LibSDL():
_size(0),
_font(nullptr),
_bloc(nullptr),
_text(nullptr),
_resetTicks(0)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1)
		throw std::invalid_argument(SDL_GetError());
	if (TTF_Init() == -1)
		throw std::invalid_argument(TTF_GetError());
	_win = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, 32,
		SDL_SWSURFACE | SDL_DOUBLEBUF);
	if (!_win)
		throw std::invalid_argument(SDL_GetError());
	SDL_WM_SetCaption("Arcade by Jodie, Kévin and Paul", NULL);
	SDL_EnableKeyRepeat(100, 100);
}

/*!
* Destructor of LibSDL's class.
* Stop the SDL library.
*/

LibSDL::~LibSDL()
{
	TTF_CloseFont(_font);
	TTF_Quit();
	SDL_FreeSurface(_text);
	SDL_FreeSurface(_bloc);
	SDL_FreeSurface(_win);
	SDL_Quit();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::displaySquare(Entity const *entity, int const size,
	std::pair<int, int> const &mapSize)
{
	SDL_Rect	pos;
	pos.x = (short int) ((WIN_WIDTH - mapSize.first * size) / 2
		+ entity->getPos().first * size);
	pos.y = (short int) ((WIN_HEIGHT - mapSize.second * size) / 2
		+ entity->getPos().second * size);

	_bloc = SDL_CreateRGBSurface(SDL_SWSURFACE,
				size, size, 32, 0, 0, 0, 0);
	if (_bloc == NULL)
		throw std::invalid_argument(SDL_GetError());
	SDL_FillRect(_bloc, NULL, convertSquareColor(entity->getColor()));
	SDL_BlitSurface(_bloc, NULL, _win, &pos);
}

/*!
* Convert a string color into an Uint32 color.
* @param [in] colorbloc
* @return an Uint32 corresponding to the right color
*/

Uint32	LibSDL::convertSquareColor(std::string const &color)
{
	std::unordered_map<std::string, Uint32>	colors = {
		{"red", SDL_MapRGB(_win->format, 255, 0, 0)}, \
		{"blue", SDL_MapRGB(_win->format, 0, 0, 255)}, \
		{"green", SDL_MapRGB(_win->format, 0, 255, 0)}, \
		{"yellow", SDL_MapRGB(_win->format, 255, 255, 0)}, \
		{"white", SDL_MapRGB(_win->format, 255, 255, 255)}, \
		{"black", SDL_MapRGB(_win->format, 0, 0, 0)}
	};
	return colors[color];
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::displayText(std::pair<int, int> textPos, std::string str,
	std::string const &color, int size)
{
	SDL_Rect pos;
	pos.x = textPos.first - (str.size() * size) / 2;
	pos.y = textPos.second - size / 2;

	if (_font)
		TTF_CloseFont(_font);
	_font = TTF_OpenFont("./lib/font/arcade.ttf", size);
	if (!_font)
		throw std::invalid_argument(TTF_GetError());
	_text = TTF_RenderText_Blended(_font, str.c_str(),
		convertTextColor(color));
	SDL_BlitSurface(_text, NULL, _win, &pos);
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

SDL_Color	LibSDL::convertTextColor(std::string const &color)
{
	std::unordered_map<std::string, SDL_Color>	colors = {
		{"red", {255, 0, 0}}, \
		{"blue", {0, 0, 255}}, \
		{"green", {0, 255, 0}}, \
		{"orange", {255, 69, 0}}, \
		{"yellow", {255, 255, 0}}, \
		{"white", {255, 255, 255}}, \
		{"black", {0, 0, 0}}
	};
	return colors[color];
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::displayMenuButton(std::string name, std::pair<int, int> start,
	std::pair<int, int> size)
{
	if (_font)
		TTF_CloseFont(_font);
	_font = TTF_OpenFont("./lib/font/arcade.ttf", 30);
	_text = TTF_RenderText_Blended(_font, name.c_str(), {255, 0, 0});

	SDL_Rect pos = {
		(int short) ((size.first - name.size() * 30) / 2),
		(int short) ((size.second - 30) / 2)
	};

	_bloc = SDL_CreateRGBSurface(SDL_SWSURFACE,
			size.first, size.second, 32, 0, 0, 0, 0);
	SDL_FillRect(_bloc, NULL, SDL_MapRGB(_win->format, 0, 255, 255));
	SDL_BlitSurface(_text, NULL, _bloc, &pos);

	pos.x = start.first - size.first / 2;
	pos.y = start.second - size.second / 2;
	SDL_BlitSurface(_bloc, NULL, _win, &pos);
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::updateScreen()
{
	SDL_Flip(_win);
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::clearWindow()
{
	SDL_FillRect(_win, NULL, SDL_MapRGB(_win->format, 0, 0, 0));
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventKey	LibSDL::getKeyPressed()
{
	std::unordered_map<int, eventKey>	keys = {
		{SDLK_ESCAPE, ESCAPE}, {SDLK_BACKSPACE, BACKSPACE}, \
		{SDLK_z, Z}, {SDLK_q, Q}, \
		{SDLK_s, S}, {SDLK_d, D}, \
		{SDLK_r, R}, {SDLK_UP, UP}, \
		{SDLK_RIGHT, RIGHT}, {SDLK_DOWN, DOWN}, \
		{SDLK_LEFT, LEFT}
	};

	SDL_Event	event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
		return ESCAPE;
	else if (event.type == SDL_KEYDOWN && keys[event.key.keysym.sym])
		return keys[event.key.keysym.sym];
	return NOKEY;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

eventKey	LibSDL::waitForMenuKey()
{
	std::unordered_map<int, eventKey>	keys = {
		{SDLK_ESCAPE, ESCAPE}, {SDLK_BACKSPACE, BACKSPACE}, \
		{SDLK_LEFT, LEFT}, {SDLK_RIGHT, RIGHT}, \
		{SDLK_RETURN, ENTER}
	};

	while (1) {
		SDL_Event	event;
		SDL_WaitEvent(&event);

		if (event.type == SDL_QUIT)
			return ESCAPE;
		else if (event.type == SDL_KEYDOWN && keys[event.key.keysym.sym])
			return keys[event.key.keysym.sym];
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

char	LibSDL::waitForCharKey()
{
	std::unordered_map<int, char>	keys = {
		{SDLK_a, 'A'}, {SDLK_b, 'B'}, {SDLK_c, 'C'}, {SDLK_d, 'D'}, \
		{SDLK_e, 'E'}, {SDLK_f, 'F'}, {SDLK_g, 'G'}, {SDLK_h, 'H'}, \
		{SDLK_i, 'I'}, {SDLK_j, 'J'}, {SDLK_k, 'K'}, {SDLK_l, 'L'}, \
		{SDLK_m, 'M'}, {SDLK_n, 'N'}, {SDLK_o, 'O'}, {SDLK_p, 'P'}, \
		{SDLK_q, 'Q'}, {SDLK_r, 'R'}, {SDLK_s, 'S'}, {SDLK_t, 'T'}, \
		{SDLK_u, 'U'}, {SDLK_v, 'V'}, {SDLK_w, 'W'}, {SDLK_x, 'X'}, \
		{SDLK_y, 'Y'}, {SDLK_z, 'Z'}
	};

	while (1) {
		SDL_Event	event;
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN && keys[event.key.keysym.sym])
			return keys[event.key.keysym.sym];
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	LibSDL::getTimer()
{
	return SDL_GetTicks();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	LibSDL::resetTimer()
{
	_resetTicks = SDL_GetTicks();
}

/*!
* Let us get an instance of the LibSDL class without paying
* attention to compilator mangling
* @return a new instance of the "LibSDL" class
*/

extern "C"
{
	IGraphical	*getInstance()
	{
		return new LibSDL();
	}
}
