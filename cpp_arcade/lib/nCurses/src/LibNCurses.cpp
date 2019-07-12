/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibNCurses
*/

#include "LibNCurses.hpp"

LibNCurses::LibNCurses()
{
	struct timeval tp;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	timeout(500);
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	gettimeofday(&tp, NULL);
	this->_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

LibNCurses::~LibNCurses()
{
	endwin();
}

int LibNCurses::choose_color(std::string const color)
{
	std::unordered_map<std::string, int>	colors = {
		{"red", 3}, \
		{"blue", 1}, \
		{"yellow", 4}, \
		{"white", 2}, \
		{"black", 5}, \
		{"green", 6}, \
		{"orange", 3}
	};
	return (COLOR_PAIR(colors[color]));
}

void LibNCurses::displaySquare(Entity const *entity, \
				int const size, \
				std::pair<int, int> const &mapSize)
{
	int x = std::get<0>(entity->getPos()) + (COLS / 2) - \
	(std::get<0>(mapSize) / 2);
	int y = std::get<1>(entity->getPos()) + (LINES / 2) - \
	(std::get<1>(mapSize) / 2);

	if (has_colors() == FALSE)
		throw std::invalid_argument("Your terminal does not \
support colors");
	wmove(stdscr, y, x);
	attron(choose_color(entity->getColor()));
	waddch(stdscr, entity->getChar());
}

void LibNCurses::updateScreen()
{
	refresh();
}

void LibNCurses::clearWindow()
{
	wmove(stdscr, 0, 0);
	for (size_t i = 0; i < LINES; i++)
		waddch(stdscr, '\n');

}

eventKey LibNCurses::get_key(int ch)
{
	std::unordered_map<int, eventKey>	keys = {
		{27, ESCAPE}, \
		{KEY_BACKSPACE, BACKSPACE}, \
		{122, Z}, {113, Q}, {115, S}, {100, D}, {114, R}, \
		{KEY_UP, UP}, \
		{KEY_RIGHT, RIGHT}, \
		{KEY_DOWN, DOWN}, \
		{KEY_LEFT, LEFT}
	};
	if (keys[ch])
		return (keys[ch]);
	else
		return (NOKEY);
}

eventKey LibNCurses::getKeyPressed()
{
	int ch = 0;

	ch = getch();
	if (ch == ERR)
		return (NOKEY);
	if (ch == KEY_RESIZE)
		clear();
	return (get_key(ch));
}

int	LibNCurses::getTimer()
{
	struct timeval tp;
	int current;

	gettimeofday(&tp, NULL);
	current = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return current - this->_time;
}

eventKey LibNCurses::waitForMenuKey()
{
	std::unordered_map<int, eventKey>	keys = {
		{27, ESCAPE}, {KEY_BACKSPACE, BACKSPACE}, \
		{KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT}, \
		{10, ENTER}
	};
	int ch;

	while (1) {
		ch = getch();
		if (keys[ch])
			return keys[ch];
	}
}

void LibNCurses::displayText(std::pair<int, int> textPos, std::string str,
	std::string const &color, int size)
{
	float cols = (float)COLS / (float)1920;
	float lines = (float)LINES / (float)1080;
	float x = ((float)(std::get<0>(textPos)) * cols) - (str.size() / 2);
	float y = (float)(std::get<1>(textPos)) * lines;

	attron(choose_color(color));
	mvprintw(y, x, "%s", str.c_str());
}

void LibNCurses::displayMenuButton(std::string name, std::pair<int, int> pos,
	std::pair<int, int> size)
{
	float cols = (float)COLS / (float)1920;
	float lines = (float)LINES / (float)1080;
	float x = ((float)(std::get<0>(pos)) * cols) - (name.size() / 2);
	float y = (float)(std::get<1>(pos)) * lines;

	attron(choose_color("red"));
	mvprintw(y, x, "%s", name.c_str());
}

char LibNCurses::waitForCharKey()
{
	std::unordered_map<int, char>	keys = {
		{97, 'A'}, {98, 'B'}, {99, 'C'}, {100, 'D'}, \
		{101, 'E'}, {102, 'F'}, {103, 'G'}, {104, 'H'}, \
		{105, 'I'}, {106, 'J'}, {107, 'K'}, {108, 'L'}, \
		{109, 'M'}, {110, 'N'}, {111, 'O'}, {112, 'P'}, \
		{113, 'Q'}, {114, 'R'}, {115, 'S'}, {116, 'T'}, \
		{117, 'U'}, {118, 'V'}, {119, 'W'}, {120, 'X'}, \
		{121, 'Y'}, {122, 'Z'}
	};
	int ch;

	while (1) {
		ch = getch();
		if (keys[ch])
			return keys[ch];
	}
}

void	LibNCurses::resetTimer()
{
	struct timeval tp;
	int current;

	gettimeofday(&tp, NULL);
	current = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	this->_time = current;
}

/*!
* Let us get an instance of the LibSFML class without paying
* attention to compilator mangling
* @return a new instance of the "LibSFML" class
*/
extern "C"
{
	IGraphical *getInstance(void)
	{
		return new LibNCurses();
	}
}
