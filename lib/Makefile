##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

RM		=	rm -f

DIR_NCURSES	=	nCurses/

LIB_NCURSES	=	lib_arcade_ncurses.so

DIR_SDL	=	sdl/

LIB_SDL	=	lib_arcade_sdl.so

DIR_ALLEGRO	=	allegro/

LIB_ALLEGRO	=	lib_arcade_allegro.so

all:	sdl ncurses

all_bis:    sdl ncurses allegro

allegro:
	$(MAKE) -C $(DIR_ALLEGRO)
	cp $(DIR_ALLEGRO)$(LIB_ALLEGRO) .

ncurses:
	$(MAKE) -C $(DIR_NCURSES)
	cp $(DIR_NCURSES)$(LIB_NCURSES) .

sdl:
	$(MAKE) -C $(DIR_SDL)
	cp $(DIR_SDL)$(LIB_SDL) .

clean:
	$(MAKE) clean -C $(DIR_ALLEGRO)
	$(MAKE) clean -C $(DIR_NCURSES)
	$(MAKE) clean -C $(DIR_SDL)

fclean:	clean
	$(MAKE) fclean -C $(DIR_ALLEGRO)
	$(MAKE) fclean -C $(DIR_NCURSES)
	$(MAKE) fclean -C $(DIR_SDL)
	$(RM) $(LIB_NCURSES)
	$(RM) $(LIB_ALLEGRO)
	$(RM) $(LIB_SDL)

re:	fclean all

.PHONY:	clean fclean ncurses sdl allegro all_bis