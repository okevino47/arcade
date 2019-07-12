/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** libNCurses header
*/

#ifndef LIBNCURSES_HPP_
	#define LIBNCURSES_HPP_

	#include "IGraphical.hpp"
	#include <ncurses.h>
	#include <signal.h>
	#include <unordered_map>
	#include <sys/time.h>

	class LibNCurses: public IGraphical
	{
		public:
			LibNCurses();
			~LibNCurses();

		void		displaySquare(Entity const *entity, \
					int const size, \
					std::pair<int, int> const &);
		void		updateScreen();
		void		clearWindow();
		eventKey	getKeyPressed();
		int		getTimer();
		eventKey	waitForMenuKey();
		void		displayText(std::pair<int, int> textPos, \
					std::string str, \
					std::string const &color, int size);
		void		displayMenuButton(std::string name, \
					std::pair<int, int> pos, \
					std::pair<int, int> size);
		char		waitForCharKey();
		void		resetTimer();

		private:
			int		choose_color(std::string const color);
			eventKey	get_key(int ch);

			int _time;
	};

#endif /* !LIBNCURSES_HPP_ */
