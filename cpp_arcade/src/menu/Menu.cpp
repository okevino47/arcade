/*
** EPITECH PROJECT, 2018
** Menu.cpp
** File description:
** function
*/

#include "Menu.hpp"

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Menu::Menu()
{}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

Menu::~Menu()
{}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::runPage1(IGraphical *lib, std::string str)
{
	(void) str;
	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			"Press ENTER to continue", "green", 30);
	lib->updateScreen();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::runPage2(IGraphical *lib, std::string str)
{
	std::string	tmp(str);
	for (size_t i = 0; i < tmp.size(); i++)
		if (tmp[i] == ' ')
			tmp[i] = '_';

	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2),
			"Enter your nickname " + tmp, "blue", 45);
	lib->displayText(std::make_pair(WIN_WIDTH / 2,
			WIN_HEIGHT / 2 + 45 * 2),
			"Press ENTER to continue", "green", 30);
	lib->updateScreen();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::runPage3(IGraphical *lib, std::string str)
{
	lib->displayMenuButton("< " + str + " >",
		std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2),
		std::make_pair(600, 200));
	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 200),
		"Press ENTER to continue", "green", 30);
	lib->updateScreen();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::runPage4(IGraphical *lib, std::string str)
{
	lib->displayMenuButton("< " + str + " >",
		std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2),
		std::make_pair(600, 200));
	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 200),
		"Press ENTER to continue", "green", 30);
	lib->updateScreen();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::runPage5(IGraphical *lib, std::string str)
{
	int		i = 0;
	std::ifstream	file("./score/" + str + ".txt");
	std::string	line;

	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2 - 100),
		"Scores of " + str, "yellow", 30);
	if (file.is_open()) {
		while (getline(file, line) && i < 8) {
			lib->displayText(std::make_pair(WIN_WIDTH / 2,
				WIN_HEIGHT / 2 - 30 + 40 * i),
				line, "red", 30);
			i++;
		}
	}
	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 330),
		"Press ENTER to continue", "green", 30);
	lib->updateScreen();
}

/**
* @brief <brief>
* @param [in] <name> <parameter_description>
* @return <return_description>
* @details <details>
*/

void	Menu::displayUI(IGraphical *lib, std::string lname)
{
	std::string	help("Escape: quit - Enter: continue\
 - Backspace: previous");

	lib->clearWindow();
	lib->displayText(std::make_pair((int) lname.size() * 15, 15),
		lname, "white", 15);
	lib->displayText(std::make_pair(WIN_WIDTH / 2, 200),
		"ARCADE", "orange", 200);
	lib->displayText(std::make_pair(WIN_WIDTH / 2, WIN_HEIGHT - 100),
		help, "blue", 20);
}
