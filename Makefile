##
## EPITECH PROJECT, 2022
## MAKEFILE
## File description:
## Makefile
##

NAME = my_touch

SRC = 	src/create_file.c	\
	src/project_name.c	\
	src/utils.c	\
	src/build.c	\
	src/file_engine.c	\
	src/parser.c	\
	src/formater.c	\
	src/my_touch.c	\
	src/makefile/dir.c	\
	src/makefile/makefile_builder.c	\

OBJ = 	$(SRC:.c=.o)

CFLAGS = -I include -W -Wall -Wextra

all:	$(NAME)

$(NAME) : $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f vgcore.*
	rm -f Test

fclean: clean
	rm -f $(NAME)

re:	fclean all

valgrind : fclean
	gcc -o $(NAME) $(SRC) $(CFLAGS) -g

## Makefile generate by MyTouch : @charly.le-corre
