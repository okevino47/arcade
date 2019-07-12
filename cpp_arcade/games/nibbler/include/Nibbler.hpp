/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Nibbler
*/


#ifndef	NIBBLER_HPP_
# define	NIBBLER_HPP_

#include <iostream>

#include "macro.hpp"
#include "IGame.hpp"

#define	ERROR	84
#define	SUCCES	0

class	Nibbler: public IGame
{
public:
	Nibbler();
	~Nibbler();

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
	int	checkChar(Entity entity);
	void	modifyEntity(Entity entity, std::pair<int, int> pos,
		std::string const &type, char const c);

private:
	int					_end;
	std::vector<std::vector<Entity>>	_map;
	int					_size;
	int					_speed;
	std::vector<std::pair<int, int>>	_snake;
};

#endif /* NIBBLER_HPP_ */
