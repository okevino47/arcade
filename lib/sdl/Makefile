##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

++		=	g++

RM		=	rm -f

CPPFLAGS	+=	-I include -I../../include -fPIC

LDFLAGS		=	-shared -lSDL -lSDL_ttf

SRCS		=	src/LibSDL.cpp				\
			../../src/displayable/Entity.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	lib_arcade_sdl.so

all:	$(NAME)

$(NAME):	$(OBJS)
	$(++) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM)	$(OBJS)

fclean:	clean
	$(RM)	$(NAME)

re:	fclean all

.PHONY:	clean fclean
