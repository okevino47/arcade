##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

++		=	g++

RM		=	rm -f

CPPFLAGS	+=	-I./include -I../../include -fPIC

LDFLAGS		+=	`pkg-config --libs allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5` -shared -lallegro

SRCS		=	src/LibAllegro.cpp	\
                ../../src/displayable/Entity.cpp

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	lib_arcade_allegro.so

all:			$(NAME)

$(NAME):			$(OBJS)
			$(++) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

go:			re
			$(RM) $(OBJS)

.PHONY:			clean fclean
