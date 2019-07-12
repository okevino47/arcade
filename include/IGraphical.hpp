/*
** EPITECH PROJECT, 2018
** IGraphical.hpp
** File description:
** header
*/

#ifndef IGRAPHICAL_HPP_
# define	IGRAPHICAL_HPP_

#include <vector>

#include "macro.hpp"
#include "Entity.hpp"

class	IGraphical
{
public:
	virtual	~IGraphical() {};

	virtual void	displaySquare(Entity const *entity, int const size,
					std::pair<int, int> const &) = 0;
	virtual void	displayText(std::pair<int, int>, std::string str,
			std::string const &color, int size) = 0;
	virtual void	displayMenuButton(std::string name,
			std::pair<int, int>, std::pair<int, int>) = 0;
	virtual void		updateScreen() = 0;
	virtual void		clearWindow() = 0;
	virtual eventKey	getKeyPressed() = 0;
	virtual eventKey	waitForMenuKey() = 0;
	virtual char		waitForCharKey() = 0;
	virtual int		getTimer() = 0;
	virtual void		resetTimer() = 0;
};

#endif /* IGRAPHICAL_HPP_ */
