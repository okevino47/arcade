/*
** EPITECH PROJECT, 2018
** Pacman.hpp
** File description:
** header
*/

#ifndef	PACMAN_HPP_
# define	PACMAN_HPP_

#include <iostream>

#include "IGame.hpp"

class	Pacman: public IGame
{
public:
	Pacman();
	~Pacman();

	std::vector<std::vector<Entity>> const	&getMap() const;
	int					getSize() const;
	int					getSpeed() const;
	int					getEnd() const;

	int	isMoveAvailable(direction const dir);
	void	moveUp();
	void	moveLeft();
	void	moveDown();
	void	moveRight();

private:
	Entity	createEntity(char const character);
	Entity	defineEntityColorAndPos(Entity entity,
						int const x, int const y);
	int	checkCharAtPos(Entity entity);

private:
	int					_end;
	std::vector<std::vector<Entity>>	_map;
	int					_size;
	int					_speed;
	std::pair<int, int>			_pacman;
};

#endif /* PACMAN_HPP_ */
