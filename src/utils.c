/*
** EPITECH PROJECT, 2022
** utils.c
** File description:
** utils
*/

#include "my_touch.h"

int replace_mod(char **av)
{
    for (int i = 0; av[i]; i++)
        if (strcmp(av[i], "-r") == 0)
            return (O_TRUNC);
    return (O_APPEND);
}

int find_type(char *path)
{
    int i = 0;
    char *type[] = {".c", ".h", "Makefile", ".py", ".sh", ".cpp", ".hpp", NULL};

    if (strcmp(path, "Makefile") == 0)
        return (2);

    for (; path[i] != '\0' && path[i] != '.'; i++);
    if (path[i] != '.')
        return (-1);
    for (int j = 0; type[j] != NULL; j++) {
        if (strcmp(&path[i], type[j]) == 0)
            return (j);
    }
    return (-1);
}

int arg_conatain(char **arg, char *src)
{
    for (int i = 0; arg[i]; i++) {
        if (strcmp(arg[i], src) == 0)
            return (i);
    }
    return (-1);
}

int display_help(void)
{
    printf("Help: use ./my_touch [file] ...\n");
    return (84);
}

int is_letter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int error_message(char *msg)
{
    dprintf(2, RED "%s" NC, msg);
    return (84);
}