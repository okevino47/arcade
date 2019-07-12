/*
** EPITECH PROJECT, 2018
** Entity.hpp
** File description:
** header
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>
#include <utility>
#include <iostream>

class	Entity
{
public:
	Entity(std::string const &type, char const c);
	Entity();
	~Entity();

	std::string const		&getType() const;
	std::pair<int, int> const	&getPos() const;
	std::string const		&getColor() const;
	char				getChar() const;

	void	setType(std::string const &type);
	void	setPos(std::pair<int, int> const &pos);
	void	setColor(std::string const &color);
	void	setChar(char const c);

private:
	std::string		_type;
	char			_c;
	std::pair<int, int>	_pos;
	std::string		_color;
};

#endif /* !ENTITY_HPP_ */
