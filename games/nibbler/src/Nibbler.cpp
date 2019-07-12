/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

#include <string>
#include <fstream>
#include <unordered_map>

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Nibbler::Nibbler():
_end(false),
_size(30),
_speed(200)
{
	int	y = 0;
	std::ifstream	file("./games/nibbler/map/1.txt");
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

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Nibbler::~Nibbler()
{}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

std::vector<std::vector<Entity>> const	&Nibbler::getMap() const
{
	return _map;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Nibbler::getSize() const { return _size; }

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Nibbler::getSpeed() const { return _speed; }

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Nibbler::getEnd() const { return _end; }

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Entity	Nibbler::createEntity(char const character)
{
	switch (character) {
		case '#':
		return Entity("wall", character);
		case 'o':
		return Entity("apple", character);
		case 'C':
		return Entity("snake", character);
		default:
		return Entity();
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Entity	Nibbler::defineEntityColorAndPos(Entity entity,
						int const x, int const y)
{
	std::unordered_map<std::string, std::string>	colors = {
		{"wall", "blue"},
		{"apple", "green"},
		{"snake", "red"},
		{"snake", "red"},
		{"snake", "red"},
		{"", "black"}
	};

	entity.setPos(std::make_pair(x, y));
	entity.setColor(colors[entity.getType()]);
	if (entity.getType() == "snake" && _snake.size() != 3)
		_snake.push_back(std::make_pair(x, y));
	return entity;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Nibbler::isMoveAvailable(direction const dir)
{
	if (dir == UPDIR
		&& !checkChar(_map[_snake[0].second - 1][_snake[0].first]))
		return SUCCES;
	else if (dir == LEFTDIR
		&& !checkChar(_map[_snake[0].second][_snake[0].first - 1]))
		return SUCCES;
	else if (dir == DOWNDIR
		&& !checkChar(_map[_snake[0].second + 1][_snake[0].first]))
		return SUCCES;
	else if (dir == RIGHTDIR
		&& !checkChar(_map[_snake[0].second][_snake[0].first + 1]))
		return SUCCES;
	return FAIL;
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

int	Nibbler::checkChar(Entity entity)
{
	switch (entity.getChar()) {
		case ' ':
			return SUCCES;
		case 'o':
			return SUCCES;
		case 'C':
			_end = true;
			return SUCCES;
		default:
			return FAIL;
	}
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Nibbler::modifyEntity(Entity entity, std::pair<int, int> pos,
	std::string const &type, char const c)
{
	int	x = pos.first;
	int	y = pos.second;

	_map[y][x].setType(type);
	_map[y][x].setChar(c);
	_map[y][x] = defineEntityColorAndPos(_map[y][x], x, y);
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Nibbler::moveUp()
{
	std::pair<int, int>	xy;
	size_t	len = _snake.size();

	if (isMoveAvailable(UPDIR) == FAIL)
		return ;
	for (size_t i = 1; i < len - 1; i++) {
		xy = std::make_pair(_snake[i].first, _snake[i].second);
		_snake[i] = _snake[i - 1];
	}
	_snake[0].second--;
	std::pair<int, int>	tmp = xy;
	xy = std::make_pair(_snake[len - 1].first, _snake[len - 1].second);
	_snake[len - 1] = tmp;
	modifyEntity(_map[xy.second][xy.first], xy, "", ' ');
	xy = std::make_pair(_snake[0].first, _snake[0].second);
	modifyEntity(_map[xy.second][xy.first], xy, "snake", 'C');
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Nibbler::moveLeft()
{
	std::pair<int, int>	xy;
	size_t	len = _snake.size();

	if (isMoveAvailable(LEFTDIR) == FAIL)
		return ;
	for (size_t i = 1; i < len - 1; i++) {
		xy = std::make_pair(_snake[i].first, _snake[i].second);
		_snake[i] = _snake[i - 1];
	}
	_snake[0].first--;
	std::pair<int, int>	tmp = xy;
	xy = std::make_pair(_snake[len - 1].first, _snake[len - 1].second);
	_snake[len - 1] = tmp;
	modifyEntity(_map[xy.second][xy.first], xy, "", ' ');
	xy = std::make_pair(_snake[0].first, _snake[0].second);
	modifyEntity(_map[xy.second][xy.first], xy, "snake", 'C');
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Nibbler::moveDown()
{
	std::pair<int, int>	xy;
	size_t	len = _snake.size();

	if (isMoveAvailable(DOWNDIR) == FAIL)
		return ;
	for (size_t i = 1; i < len - 1; i++) {
		xy = std::make_pair(_snake[i].first, _snake[i].second);
		_snake[i] = _snake[i - 1];
	}
	_snake[0].second++;
	std::pair<int, int>	tmp = xy;
	xy = std::make_pair(_snake[len - 1].first, _snake[len - 1].second);
	_snake[len - 1] = tmp;
	modifyEntity(_map[xy.second][xy.first], xy, "", ' ');
	xy = std::make_pair(_snake[0].first, _snake[0].second);
	modifyEntity(_map[xy.second][xy.first], xy, "snake", 'C');
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Nibbler::moveRight()
{
	std::pair<int, int>	xy;
	size_t	len = _snake.size();

	if (isMoveAvailable(RIGHTDIR) == FAIL)
		return ;
	for (size_t i = 1; i < len - 1; i++) {
		xy = std::make_pair(_snake[i].first, _snake[i].second);
		_snake[i] = _snake[i - 1];
	}
	_snake[0].first++;
	std::pair<int, int>	tmp = xy;
	xy = std::make_pair(_snake[len - 1].first, _snake[len - 1].second);
	_snake[len - 1] = tmp;
	modifyEntity(_map[xy.second][xy.first], xy, "", ' ');
	xy = std::make_pair(_snake[0].first, _snake[0].second);
	modifyEntity(_map[xy.second][xy.first], xy, "snake", 'C');
}

/*!
* Allow us to get a new instance of Nibbler class
* without paying attention to compilator mangling.
* @return new instance of Nibbler class
*/

extern "C"
{
	IGame	*getInstance()
	{
		return new Nibbler();
	}
}
