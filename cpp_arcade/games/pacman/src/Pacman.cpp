/*
** EPITECH PROJECT, 2018
** Pacman.cpp
** File description:
** function
*/

#include "Pacman.hpp"

#include <string>
#include <fstream>
#include <unordered_map>

/*!
* Constructor of Pacman class.
* Instanciate and parse the map.
*/

Pacman::Pacman():
_end(false),
_size(30),
_speed(200)
{
	int	y = 0;
	std::ifstream	file("./games/pacman/map/map.txt");
	std::string	line;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::vector<Entity>	tmp;
			for (size_t x = 0; x < line.size(); x++) {
				Entity	entity = createEntity(line[x]);
				entity = defineEntityColorAndPos(entity, x, y);
				tmp.push_back(entity);
			}
			_map.push_back(tmp);
			y++;
		}
	}
}

/*!
* Destructor of Pacman class.
*/

Pacman::~Pacman()
{}

/*!
* Getter method of Entity class to get the value of
* "_map" attribute.
* @return "_map" value
*/

std::vector<std::vector<Entity>> const	&Pacman::getMap() const
{
	return _map;
}

/*!
* Getter method of Entity class to get the value of
* "_size" attribute.
* @return "_size" value
*/

int	Pacman::getSize() const { return _size; }

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Pacman::getSpeed() const { return _speed; }

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Pacman::getEnd() const { return _end; }

/*!
* Call the constructor of Entity class with the right
* parameter looking at the character.
* @param [in] character
* @return an Entity class with the right type
*/

Entity	Pacman::createEntity(char const character)
{
	switch (character) {
		case '#':
		return Entity("wall", character);
		case '*':
		return Entity("pacgum1", character);
		case 'o':
		return Entity("pacgum2", character);
		case '$':
		return Entity("ghost", character);
		case 'C':
		return Entity("pacman", character);
		default:
		return Entity();
	}
}

/*!
* Set the position and the color of the entity passed
* as parameter.
* @param [in/out] entity
* @param [in] x
* @param [in] y
* @return the modified entity passed as parameter
*/

Entity	Pacman::defineEntityColorAndPos(Entity entity,
						int const x, int const y)
{
	std::unordered_map<std::string, std::string>	colors = {
		{"wall", "blue"},
		{"pacgum1", "white"},
		{"pacgum2", "green"},
		{"ghost", "red"},
		{"pacman", "yellow"},
		{"", "black"}
	};

	entity.setPos(std::make_pair(x, y));
	entity.setColor(colors[entity.getType()]);
	if (entity.getType() == "pacman")
		_pacman = std::make_pair(x, y);
	return entity;
}

/*!
* Check if there is a wall or not looking at
* the direction taken.
* @param [in] dir
* @return "SUCCES" if the move is available
*	  "FAIL" if not
*/

int	Pacman::isMoveAvailable(direction const dir)
{
	if (dir == UPDIR
		&& !checkCharAtPos(_map[_pacman.second - 1][_pacman.first]))
		return SUCCES;
	else if (dir == LEFTDIR && (_pacman.first == 0
		|| !checkCharAtPos(_map[_pacman.second][_pacman.first - 1])))
		return SUCCES;
	else if (dir == DOWNDIR
		&& !checkCharAtPos(_map[_pacman.second + 1][_pacman.first]))
		return SUCCES;
	else if (dir == RIGHTDIR && (_pacman.first == _map[0].size() - 1
		|| !checkCharAtPos(_map[_pacman.second][_pacman.first + 1])))
		return SUCCES;
	return FAIL;
}

int	Pacman::checkCharAtPos(Entity	entity)
{
	switch (entity.getChar()) {
		case ' ':
			return SUCCES;
		case '*':
			return SUCCES;
		case 'o':
			return SUCCES;
		case '$':
			_end = true;
			return SUCCES;
		default:
			return FAIL;
		}
}

/*!
* Move pacman to up position.
*/

void	Pacman::moveUp()
{
	int	x = _pacman.first;
	int	y = _pacman.second;

	if (isMoveAvailable(UPDIR) == FAIL)
		return ;
	_map[y][x].setType("");
	_map[y][x].setChar(' ');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
	_map[y - 1][x].setType("pacman");
	_map[y - 1][x].setChar('C');
	_map[y - 1][x] = defineEntityColorAndPos(_map[y - 1][x], x, y - 1);
}

/*!
* Move pacman to left position.
*/

void	Pacman::moveLeft()
{
	int	x = _pacman.first;
	int	y = _pacman.second;

	if (isMoveAvailable(LEFTDIR) == FAIL)
		return ;
	_map[y][x].setType("");
	_map[y][x].setChar(' ');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
	x = x == 0 ? _map[0].size() - 1 : x - 1;
	_map[y][x].setType("pacman");
	_map[y][x].setChar('C');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
}

/*!
* Move pacman to down position.
*/

void	Pacman::moveDown()
{
	int	x = _pacman.first;
	int	y = _pacman.second;

	if (isMoveAvailable(DOWNDIR) == FAIL)
		return ;
	_map[y][x].setType("");
	_map[y][x].setChar(' ');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
	_map[y + 1][x].setType("pacman");
	_map[y + 1][x].setChar('C');
	_map[y + 1][x] = defineEntityColorAndPos(_map[y + 1][x], x, y + 1);
}

/*!
* Move pacman to right position.
*/

void	Pacman::moveRight()
{
	int	x = _pacman.first;
	int	y = _pacman.second;

	if (isMoveAvailable(RIGHTDIR) == FAIL)
		return ;
	_map[y][x].setType("");
	_map[y][x].setChar(' ');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
	x = x == _map[0].size() - 1 ? 0 : x + 1;
	_map[y][x].setType("pacman");
	_map[y][x].setChar('C');
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
}

/*!
* Allow us to get a new instance of Pacman class
* without paying attention to compilator mangling.
* @return new instance of Pacman class
*/

extern "C"
{
	IGame	*getInstance()
	{
		return new Pacman();
	}
}
