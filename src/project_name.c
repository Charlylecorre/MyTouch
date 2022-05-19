/*
** EPITECH PROJECT, 2022
** project name.c
** File description:
** project name
*/

#include "my_touch.h"

char *get_project_name(char *path)
{
    char *project;
    int len = 0;

    for (int i = 0; path[i] != '\0' && path[i] != '.'; i++)
        len++;
    project = malloc(sizeof(char) * (len + 1));
    for (int i = 0; project != NULL && path[i] != '.' && path[i] != '\0'; i++) {
        project[i] = path[i];
        if (path[i] == '_')
            project[i] = ' ';
        project[i + 1] = '\0';
    }
    return (project);
}