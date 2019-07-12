//
// EPITECH PROJECT, 2018
// LibQT.hpp
// File description:
// header
//

#ifndef LIBQT_HPP_
# define        LIBQT_HPP_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <exception>
#include <string>
#include <unordered_map>

#include "IGraphical.hpp"

class   LibAllegro: public IGraphical
{
public:
	LibAllegro();
	~LibAllegro();

	void		displaySquare(Entity const *entity, int const size,
				  std::pair<int, int> const &mapStart);
	void		updateScreen();
	void		clearWindow();
	eventKey	getKeyPressed();
	int		getTimer();
	void	displayText(std::pair<int, int>, std::string str, \
	std::string const &color, int size);
	void	displayMenuButton(std::string name, \
	std::pair<int, int>, std::pair<int, int>);
	eventKey	waitForMenuKey();
	char		waitForCharKey();
	void		resetTimer();

private:
	int	initDisplay();
	int	initTimer();
	int 	initEventQueue();
	int	initFont(int size);
	int	initBitmap(int width, int height);
	ALLEGRO_COLOR	convertColor(std::string const &color);

	ALLEGRO_DISPLAY		*_window;
	ALLEGRO_TIMER		*_timer;
	ALLEGRO_EVENT_QUEUE	*_eventQueue;
	ALLEGRO_BITMAP		*_wall;
	ALLEGRO_FONT		*_font;
	bool 			_redraw;
	int 			_width;
	int	 		_height;
	std::string		_winName;
};

#endif /* LIBQT_HPP_ */
