##
## EPITECH PROJECT, 2022
## MAKEFILE
## File description:
## Makefile
##

NAME = my_touch

SRC =	src/create_file.c	\
     	src/project_name.c	\
     	src/utils.c	\
     	src/build.c	\
     	src/file_engine.c	\
     	src/config.c	\
     	src/parser.c	\
     	src/formater.c	\
     	src/my_touch.c	\
     	src/makefile/dir.c	\
     	src/makefile/makefile_builder.c	\
     	src/makefile/getlib/getlib.c	\

OBJ = 	$(SRC:.c=.o)

CFLAGS = -I include/ -W -Wall -Wextra

LIBS = -lncurses

all:	$(NAME)

$(NAME) : $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)
	cp $(NAME) ..
	echo "[0;32mBuild complete ![0m"
clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f vgcore.*
	rm -f Test

fclean: clean
	rm -f $(NAME)

re:	fclean all

valgrind :	fclean
	gcc -o $(NAME) $(SRC) $(CFLAGS) -g

reload :
	my_touch Makefile -r

## Makefile generate by MyTouch : @charly.le-corre
