/*
** EPITECH PROJECT, 2022
** build.c
** File description:
** build
*/

#include "my_touch.h"

char *build_hpp_link(char **arg)
{
    int len = strlen(arg[0]) + strlen(".hpp");
    char *hpp = NULL;

    hpp = malloc(sizeof(char) * (len + 1));
    if (hpp == NULL)
        return (NULL);
    strcpy(hpp, arg[0]);
    strcat(hpp, ".hpp");
    return (hpp);
}

char *build_path(char *file, char *ext)
{
    int len = 0;
    char *path = NULL;

    if (ext == NULL) {
        path = strdup(file);
        return (path);
    }
    len = strlen(file) + strlen(ext) + 1;
    path = malloc(sizeof(char) * (len + 1));
    strcpy(path, file);
    strcat(path, ".");
    strcat(path, ext);
    return (path);
}

char *build_file_name(char *path, int type)
{
    int len = strlen(path);
    char *new_path = NULL;

    if (type == PYTHON || type == SH)
        len -= 3;
    if (type == MAKEFILE)
        len = strlen("Makefile");
    if ((new_path = malloc(sizeof(char) * (len + 1))) == NULL)
        return (NULL);
    for (int i = 0; i < len; i++) {
        new_path[i] = path[i];
        new_path[i + 1] = '\0';
    }
    return (new_path);
}