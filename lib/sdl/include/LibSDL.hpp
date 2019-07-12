/*
** EPITECH PROJECT, 2018
** LibSDL.hpp
** File description:
** header
*/

#ifndef	LIBSDL_HPP_
# define	LIBSDL_HPP_

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <unordered_map>

#include "IGraphical.hpp"

class	LibSDL: public IGraphical
{
public:
	LibSDL();
	~LibSDL();

	void	displaySquare(Entity const *entity, int const size,
		std::pair<int, int> const &mapStart);
	void	displayText(std::pair<int, int> textPos, std::string str,
		std::string const &color, int size);
	void	displayMenuButton(std::string name, std::pair<int, int> pos,
		std::pair<int, int> size);
	void		updateScreen();
	void		clearWindow();
	eventKey	getKeyPressed();
	eventKey	waitForMenuKey();
	char		waitForCharKey();
	int		getTimer();
	void		resetTimer();

private:
	Uint32	convertSquareColor(std::string const &color);
	SDL_Color	convertTextColor(std::string const &color);

private:
	SDL_Surface			*_win;
	int				_size;
	TTF_Font			*_font;
	SDL_Surface			*_bloc;
	SDL_Surface			*_text;
	Uint32				_resetTicks;
};

#endif /* LIBSDL_HPP_ */
