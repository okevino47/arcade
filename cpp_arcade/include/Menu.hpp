/*
** EPITECH PROJECT, 2018
** Menu.hpp
** File description:
** header
*/

#ifndef	MENU_HPP_
# define	MENU_HPP_

#include <string>
#include <fstream>
#include <iostream>

#include "macro.hpp"
#include "IGraphical.hpp"

class Menu
{
public:
	Menu();
	~Menu();

	void	runPage1(IGraphical *lib, std::string str);
	void	runPage2(IGraphical *lib, std::string str);
	void	runPage3(IGraphical *lib, std::string str);
	void	runPage4(IGraphical *lib, std::string str);
	void	runPage5(IGraphical *lib, std::string str);
	void	displayUI(IGraphical *lib, std::string lname);
};

#endif	/* MENU_HPP_ */
