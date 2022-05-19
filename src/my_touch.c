#include "my_touch.h"

void make_python(int fd)
{
    dprintf(fd, "#!/usr/bin/env python3\n\n");
    dprintf(fd, "import sys\n\n");
    dprintf(fd, "if __name__ == '__main__':\n");
    dprintf(fd, "    print('Yo')\n");
    dprintf(fd, "    exit(0)\n");
}

void make_makefile(char *makefile, int fd, int an)
{
    makefile_builder(makefile, fd, an);
//    dprintf(fd, "##\n");
//    dprintf(fd, "## EPITECH PROJECT, %i\n", an);
//    dprintf(fd, "## MAKEFILE\n");
//    dprintf(fd, "## File description:\n");
//    dprintf(fd, "## Makefile\n");
//    dprintf(fd, "##\n\n");
//    dprintf(fd, "NAME = \n\n");
//    dprintf(fd, "SRC = exemple.cpp\t\\\n\n");
//    dprintf(fd, "OBJ = 	$(SRC:.cpp=.o)\n\n");
//    dprintf(fd, "CFLAGS = -I include -W -Wall -Wextra\n\n");
//    dprintf(fd, "all:	$(NAME)\n\n");
//    dprintf(fd, "$(NAME) : $(OBJ)\n");
//    dprintf(fd, "	gcc -o $(NAME) $(OBJ) $(CFLAGS)\n\n");
//    dprintf(fd, "clean:\n");
//    dprintf(fd, "	rm -f $(OBJ)\n");
//    dprintf(fd, "	rm -f *~\n");
//    dprintf(fd, "	rm -f vgcore.*\n");
//    dprintf(fd, "	rm -f Test\n\n");
//    dprintf(fd, "fclean: clean\n");
//    dprintf(fd, "	rm -f $(NAME)\n\n");
//    dprintf(fd, "re:	fclean all\n\n");
//    dprintf(fd, "valgrind : fclean\n");
//    dprintf(fd, "	gcc -o $(NAME) $(SRC) $(CFLAGS) -g\n");
}

int do_hpp(char *project, char **arg, int fd, char *path)
{
    char *define = define_formateur(path);
    char *format = cpp_formater(project);

    if (define == NULL || format == NULL)
        return (error_message("Error: Allocation failed\n"));
    dprintf(fd, "\n#ifndef %s\n", define);
    dprintf(fd, "    #define %s\n\n", define);
    if (arg_conatain(arg, "cpp") != -1) {
        dprintf(fd, "class %s {\n", format);
        dprintf(fd, "public:\n");
        dprintf(fd, "    %s() = default;\n", format);
        dprintf(fd, "    ~%s() = default;\n\n", format);
        dprintf(fd, "private:\n");
        dprintf(fd, "};\n\n");
    }
    dprintf(fd, "#endif //%s\n", define);
    free(format);
    free(define);
    return (0);
}

int do_cpp(char **arg, int fd)
{
    char *hpp;

    if (arg_conatain(arg, "hpp") == -1)
        return (0);
    if ((hpp = build_hpp_link(arg)) == NULL)
        return (error_message("Error: Allocation failed\n"));
    dprintf(fd, "\n");
    dprintf(fd, "#include \"%s\"\n", hpp);
    free(hpp);
    return (0);
}

int print_header(int fd, char *path, int type, char **arg)
{
    time_t now;
    int an = 0;
    char *project = get_project_name(path);
    char *define = NULL;

    time(&now);
    struct tm *local = localtime(&now);
    an = local->tm_year + 1900;
    if (project == NULL)
        return (error_message("Error: Allocation failed\n"));

    if (type == C || type == CPP || type == HPP || type == H) {
        dprintf(fd, "/*\n");
        dprintf(fd, "** EPITECH PROJECT, %i\n", an);
        dprintf(fd, "** %s\n", path);
        dprintf(fd, "** File description:\n");
        dprintf(fd, "** %s\n", project);
        dprintf(fd, "*/\n");
        if (type == H) {
            define = define_formateur(path);
            if (define == NULL) {
                free(project);
                return (84);
            }
            dprintf(fd, "\n#ifndef %s\n", define);
            dprintf(fd, "    #define %s\n\n", define);
            dprintf(fd, "#endif //%s\n", define);
            free(define);
        }
    }

    if ((type == HPP && do_hpp(project, arg, fd, path) != 0) ||
        (type == CPP && do_cpp(arg, fd) != 0)) {
        free(project);
        return (84);
    }

    if (type == MAKEFILE)
        make_makefile(path, fd, an);
    if (type == PYTHON)
        make_python(fd);
    if (type == SH)
        dprintf(fd, "#!/bin/sh\n\n");
    if (type == C && strncmp(path, "main", strlen("main")) == 0) {
        dprintf(fd, "\n");
        dprintf(fd, "int main(int ac, char **av)\n");
        dprintf(fd, "{\n\n    return (0);\n}\n");
    }
    free(project);
    return (0);
}

int main(int ac, char **av)
{
    int replace = replace_mod(av);

    if (ac == 1)
        return (display_help());
    for (int i = 1; av[i] != NULL; i++)
        if (strcmp(av[i], "-r") != 0 && file_engine(av[i], replace) != 0)
            return (84);

    return (0);
}
