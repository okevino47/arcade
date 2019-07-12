//
// EPITECH PROJECT, 2018
// LibQT.cpp
// File description:
// function
//

#include "LibAllegro.hpp"

LibAllegro::LibAllegro(): _window(nullptr), _timer(nullptr), \
			_eventQueue(nullptr), _wall(nullptr), \
			_redraw(TRUE), _width(1920), _height(1080), \
			_winName("arcade on Allegro lib")
{
	if (al_init() == FALSE)
		throw std::invalid_argument("Err: init display");
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	initDisplay();
	initTimer();
	initEventQueue();
	if (!al_is_keyboard_installed())
		if (!al_install_keyboard())
			throw std::invalid_argument("Err: driver keyboard");
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(_eventQueue, \
	al_get_display_event_source(_window));
	al_start_timer(_timer);
}

LibAllegro::~LibAllegro()
{

	al_unregister_event_source(_eventQueue, \
	al_get_display_event_source(_window));
	al_unregister_event_source(_eventQueue, \
	al_get_keyboard_event_source());
	al_destroy_event_queue(_eventQueue);
	al_destroy_timer(_timer);
	al_destroy_bitmap(_wall);
	al_shutdown_font_addon();
	al_destroy_display(_window);
}

int	LibAllegro::initFont(int size)
{
	_font = al_load_ttf_font("./lib/font/arcade.ttf", size, 0);
	if (!_font)
		throw std::invalid_argument("Err: font init");
}

int	LibAllegro::initDisplay()
{
	_window = al_create_display(_width, _height);
	if (_window == nullptr)
		throw std::invalid_argument("Err: init display 2");
}

int	LibAllegro::initTimer()
{
	_timer = al_create_timer(1.0 / 1000);
	if (_timer == nullptr)
		throw std::invalid_argument("Err: init timer");
}

int	LibAllegro::initEventQueue()
{
	_eventQueue = al_create_event_queue();
	if (_eventQueue == nullptr)
		throw std::invalid_argument("Err: init event queue");
}

int	LibAllegro::initBitmap(int width, int height)
{
	_wall = al_create_bitmap(width, height);
	if (_wall == nullptr)
		throw std::invalid_argument("Err: init wall");
}

void	LibAllegro::displaySquare(Entity const *entity, int const size, \
	std::pair<int, int> const &mapSize)
{
	int	width = ((WIN_WIDTH - mapSize.first * size) / 2
			    + entity->getPos().first * size);
	int	height = ((WIN_HEIGHT - mapSize.second * size) / 2
			     + entity->getPos().second * size);

	if (!_wall)
		initBitmap(size, size);
	al_set_target_bitmap(_wall);
	al_clear_to_color(convertColor(entity->getColor()));
	al_set_target_bitmap(al_get_backbuffer(_window));
	al_draw_bitmap(_wall, width, height, 0);
}

void	LibAllegro::displayText(std::pair<int, int> textPos, std::string str,
				    std::string const &color, int size)
{
	int	width = textPos.first - (str.size() * size) / 2;
	int	height = textPos.second - size / 2;

	if (_font)
		al_shutdown_font_addon();
	initFont(size);
	al_draw_text(_font, convertColor(color), width, height, \
	0, str.c_str());
}

void	LibAllegro::displayMenuButton(std::string name,
					  std::pair<int, int> start,
					  std::pair<int, int> size)
{
	return;
}

ALLEGRO_COLOR	LibAllegro::convertColor(std::string const &color)
{
	std::unordered_map<std::string, ALLEGRO_COLOR>	colors = {
		{"red", al_map_rgb(255, 0, 0)}, \
		{"blue", al_map_rgb(0, 0, 255)}, \
		{"yellow", al_map_rgb(255, 255, 0)}, \
		{"white", al_map_rgb(255, 255, 255)}, \
		{"black", al_map_rgb(0, 0, 0)}
	};
	return (colors[color]);
}

void	LibAllegro::updateScreen()
{
	al_flip_display();
}

void	LibAllegro::clearWindow()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

eventKey	LibAllegro::getKeyPressed()
{
	ALLEGRO_EVENT		event;
	al_get_next_event(_eventQueue, &event);
	std::unordered_map<int, eventKey>	keys = {
		{ALLEGRO_KEY_ESCAPE, ESCAPE}, \
		{ALLEGRO_KEY_BACKSPACE, BACKSPACE}, {ALLEGRO_KEY_Z, Z}, \
		{ALLEGRO_KEY_Q, Q}, {ALLEGRO_KEY_S, S}, \
		{ALLEGRO_KEY_D, D}, {ALLEGRO_KEY_R, R}, \
		{ALLEGRO_KEY_UP, UP}, {ALLEGRO_KEY_RIGHT, RIGHT}, \
		{ALLEGRO_KEY_DOWN, DOWN}, {ALLEGRO_KEY_LEFT, LEFT}
	};

	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || \
	event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		return (ESCAPE);
	else if (event.keyboard.type == ALLEGRO_EVENT_KEY_DOWN && \
	keys[event.keyboard.keycode])
		return (keys[event.keyboard.keycode]);
	return (NOKEY);
}

int	LibAllegro::getTimer()
{
	return ((int)al_get_timer_count(_timer));
}

eventKey	LibAllegro::waitForMenuKey()
{
	ALLEGRO_EVENT		event;
	std::unordered_map<int, eventKey>	keys = {
		{ALLEGRO_KEY_ESCAPE, ESCAPE}, \
		{ALLEGRO_KEY_BACKSPACE, BACKSPACE}, \
		{ALLEGRO_KEY_LEFT, LEFT}, {ALLEGRO_KEY_RIGHT, RIGHT}, \
		{ALLEGRO_KEY_ENTER, ENTER}
	};

	while (1) {
		al_get_next_event(_eventQueue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || \
		event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			return (ESCAPE);
		else if (event.keyboard.type == ALLEGRO_EVENT_KEY_DOWN && \
		keys[event.keyboard.keycode])
			return (keys[event.keyboard.keycode]);
	}
}

char	LibAllegro::waitForCharKey()
{
	ALLEGRO_EVENT		event;
	std::unordered_map<int, char>	keys = {
		{ALLEGRO_KEY_A, 'A'}, {ALLEGRO_KEY_B, 'B'}, \
		{ALLEGRO_KEY_C, 'C'}, {ALLEGRO_KEY_D, 'D'}, \
		{ALLEGRO_KEY_E, 'E'}, {ALLEGRO_KEY_F, 'F'}, \
		{ALLEGRO_KEY_G, 'G'}, {ALLEGRO_KEY_H, 'H'}, \
		{ALLEGRO_KEY_I, 'I'}, {ALLEGRO_KEY_J, 'J'}, \
		{ALLEGRO_KEY_K, 'K'}, {ALLEGRO_KEY_L, 'L'}, \
		{ALLEGRO_KEY_M, 'M'}, {ALLEGRO_KEY_N, 'N'}, \
		{ALLEGRO_KEY_O, 'O'}, {ALLEGRO_KEY_P, 'P'}, \
		{ALLEGRO_KEY_Q, 'Q'}, {ALLEGRO_KEY_R, 'R'}, \
		{ALLEGRO_KEY_S, 'S'}, {ALLEGRO_KEY_T, 'T'}, \
		{ALLEGRO_KEY_U, 'U'}, {ALLEGRO_KEY_V, 'V'}, \
		{ALLEGRO_KEY_W, 'W'}, {ALLEGRO_KEY_X, 'X'}, \
		{ALLEGRO_KEY_Y, 'Y'}, {ALLEGRO_KEY_Z, 'Z'}
	};

	while (1) {
		al_get_next_event(_eventQueue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || \
		event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			return (ESCAPE);
		else if (event.keyboard.type == ALLEGRO_EVENT_KEY_DOWN && \
		keys[event.keyboard.keycode])
			return (keys[event.keyboard.keycode]);
	}
}

void	LibAllegro::resetTimer()
{
	return;
}

extern "C" {
	IGraphical *getInstance()
	{
		return new LibAllegro();
	}
}
