/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** function
*/

#include "Core.hpp"

/**
* Main function that loads the Core class and initializes
* libraries, then it call the arcade loop
* @param [in] ac
* @param [in] av
* @return "SUCCES" if no error occured in the initialisation
*	  or the arcade loop
*	  "ERROR" if an error occured
*/

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "USAGE: ./arcade lib_path" << std::endl;
		return 84;
	}

	Core	*core = new Core();
	int	ret;
	try {
		core->getGraphicals(av[1]);
		core->getGames();
		ret = core->arcadeLoop();
		delete core;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return ret;
}
