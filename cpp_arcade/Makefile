##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

++		=	g++

RM		=	rm -f

DIR_GRAPHICALS	=	lib/

DIR_GAMES	=	games/

CPPFLAGS	+=	-I./include/ -W -Wall -Wextra -std=c++14

LDFLAGS		=	-ldl

MAIN		=	src/main.cpp

MAIN_OBJ	=	$(MAIN:.cpp=.o)

SRCS		=	src/core/Core.cpp	\
			src/menu/Menu.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	arcade

all:	core graphicals games

core:	$(OBJS) $(MAIN_OBJ)
	$(++) -o $(NAME) $(OBJS) $(MAIN_OBJ) $(LDFLAGS)

graphicals:
	$(MAKE) -C $(DIR_GRAPHICALS)

games:
	$(MAKE) -C $(DIR_GAMES)

clean:
	$(RM)	$(OBJS)
	$(RM)	$(MAIN_OBJ)
	$(MAKE) clean -C $(DIR_GRAPHICALS)
	$(MAKE) clean -C $(DIR_GAMES)

fclean:	clean
	$(RM)	$(NAME)
	$(MAKE) fclean -C $(DIR_GRAPHICALS)
	$(MAKE) fclean -C $(DIR_GAMES)

re:	fclean all

.PHONY:	clean fclean core graphicals games
