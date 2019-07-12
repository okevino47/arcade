/*
** EPITECH PROJECT, 2018
** IGame.hpp
** File description:
** header
*/

#ifndef IGAME_HPP_
# define IGAME_HPP_

#include <vector>

#include "macro.hpp"
#include "Entity.hpp"

class	IGame
{
public:
	virtual	~IGame() {};

	virtual std::vector<std::vector<Entity>> const	&getMap() const = 0;
	virtual int	getSize() const = 0;
	virtual int	getSpeed() const = 0;
	virtual int	getEnd() const = 0;

	virtual int	isMoveAvailable(direction const dir) = 0;
	virtual void	moveLeft() = 0;
	virtual void	moveUp() = 0;
	virtual void	moveDown() = 0;
	virtual void	moveRight() = 0;
};

#endif /* IGAME_HPP_ */
