##
## EPITECH PROJECT, 2018
## Makefile
## File description:
##
##

RM		=	rm -f

DIR_NIBBLER	=	nibbler/

LIB_NIBBLER	=	lib_arcade_nibbler.so

DIR_PACMAN	=	pacman/

LIB_PACMAN	=	lib_arcade_pacman.so

all:	nibbler pacman

nibbler:
	$(MAKE) -C $(DIR_NIBBLER)
	cp $(DIR_NIBBLER)$(LIB_NIBBLER) .

pacman:
	$(MAKE) -C $(DIR_PACMAN)
	cp $(DIR_PACMAN)$(LIB_PACMAN) .

clean:
	$(MAKE) clean -C $(DIR_NIBBLER)
	$(MAKE) clean -C $(DIR_PACMAN)

fclean:	clean
	$(MAKE) fclean -C $(DIR_NIBBLER)
	$(MAKE) fclean -C $(DIR_PACMAN)
	$(RM) $(LIB_NIBBLER)
	$(RM) $(LIB_PACMAN)

re:	fclean all

.PHONY:	clean fclean nibbler pacman
