/*
** EPITECH PROJECT, 2022
** file engine.c
** File description:
** file engine
*/

#include "my_touch.h"

int file_engine(char *av, int replace)
{
    char **arg = parser(av);
    char *path = NULL;
    int len = parser_len(arg);
    int type = -1;

    //display_parser(arg);
    if (len == 1 && create_file(arg[0], find_type(arg[0]), arg, replace) != 0)
        return (84);
    for (int j = 1; j < len; j++) {
        path = build_path(arg[0], arg[j]);
        type = find_type(path);
        if (create_file(path, type, arg, replace) != 0)
            return (84);
        free(path);
    }
    free_parser(arg);
    return (0);
}