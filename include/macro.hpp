/*
** EPITECH PROJECT, 2018
** macro.hpp
** File description:
** header
*/

#ifndef MACRO_HPP_
#define MACRO_HPP_

#define	FAIL	1
#define	SUCCES	0
#define	ERROR	84

#define	WIN_WIDTH	1920
#define	WIN_HEIGHT	1080

typedef enum	eventKey
{
	ESCAPE	= 10,
	BACKSPACE,
	Z,
	Q,
	S,
	D,
	R,
	ENTER,
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NOKEY
}		eventKey;

typedef enum	eventStatus
{
	QUIT = 30,
	BREAK,
	CHANGEDIR,
	NOEVENT
}		eventStatus;

typedef enum	direction
{
	UPDIR = 40,
	LEFTDIR,
	DOWNDIR,
	RIGHTDIR,
	NONE
}		direction;

#endif /* !MACRO_HPP_ */
