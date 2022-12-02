#include "my_touch.h"

void make_python(int fd)
{
    dprintf(fd, "#!/usr/bin/env python3\n\n");
    dprintf(fd, "import sys\n\n");
    dprintf(fd, "if __name__ == '__main__':\n");
    dprintf(fd, "    print('Yo')\n");
    dprintf(fd, "    exit(0)\n");
}

int do_hpp(char *project, char **arg, int fd, char *path)
{
    char *define = define_formateur(path);
    char *format = cpp_formater(project);

    if (define == NULL || format == NULL)
        return (error_message("Error: Allocation failed\n"));
    dprintf(fd, "\n#ifndef %s\n", define);
    dprintf(fd, "    #define %s\n\n", define);
    dprintf(fd, "    //#include <iostream>\n\n");
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
        return (error_message(RED"Error: Allocation failed\n"NC));
    dprintf(fd, "\n");
    dprintf(fd, "#include \"%s\"\n", hpp);
    free(hpp);
    return (0);
}

int print_header(int fd, char *path, int type, char **arg, config_t *config)
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
        makefile_builder(fd, an, arg, config);
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
    config_t *config = init_config(av);
    int replace = replace_mod(av);

    if (config == NULL)
        return (error_message(RED"Error: Allocation failed\n"NC));
    if (config->debug_mode == true)
        printf(CYN"debug : ✅\n"NC);
    if (ac == 1)
        return (display_help());
    for (int i = 1; av[i] != NULL; i++)
        if (multi_cmp(2, av[i], "-r", "-debug") != 1 && strstart(av[i], "-name:") != 0 && file_engine(av[i], replace, config) != 0) {
            free_config(config);
            return (84);
        }
    free_config(config);
    return (0);
}
