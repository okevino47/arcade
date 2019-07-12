/*
** EPITECH PROJECT, 2018
** Entity.cpp
** File description:
** function
*/

#include "Entity.hpp"

/*!
* Constructor of Entity class.
* @param [in] type;
* @param [in] c;
*/

Entity::Entity(std::string const &type, char const c): _type(type), _c(c)
{}

/*!
* Constructor of Entity class.
*/

Entity::Entity(): _type(""), _c(' ')
{}

/*!
* Destructor of Entity class.
*/

Entity::~Entity()
{}

/*!
* Getter method of Entity class to get the value of
* "_type" attribute.
* @return "_type" value
*/

std::string const	&Entity::getType() const { return _type; }

/*!
* Getter method of Entity class to get the value of
* "_pos" attribute.
* @return "_pos" value
*/

std::pair<int, int> const	&Entity::getPos() const { return _pos; }

/*!
* Getter method of Entity class to get the value of
* "_color" attribute.
* @return "_color" value
*/

std::string const	&Entity::getColor() const { return _color; }

/*!
* Getter method of Entity class to get the value of
* "_c" attribute.
* @return "_c" value
*/

char	Entity::getChar() const { return _c; }

/*!
* Setter method of Entity class to set the value of
* "_type" attribute.
* @param [in] type
*/

void	Entity::setType(std::string const &type) { _type = type; }

/*!
* Setter method of Entity class to set the value of
* "_pos" attribute.
* @param [in] pos
*/

void	Entity::setPos(std::pair<int, int> const &pos) { _pos = pos; }

/*!
* Setter method of Entity class to set the value of
* "_color" attribute.
* @param [in] color
*/

void	Entity::setColor(std::string const &color) { _color = color; }

/*!
* Setter method of Entity class to set the value of
* "_c" attribute.
* @param [in] c
*/

void	Entity::setChar(char const c) { _c = c; }
