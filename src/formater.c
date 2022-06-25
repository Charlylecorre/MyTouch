/*
** EPITECH PROJECT, 2022
** formater.c
** File description:
** formater
*/

#include "my_touch.h"

char *define_formateur(char *define)
{
    char c;
    char *new = malloc(sizeof(char) * (strlen(define) + 1));
    int i = 0;

    if (new == NULL)
        return (NULL);
    for (; define[i] != '\0'; i++) {
        c = define[i];
        if ((c >= 'a' && c <= 'z') && c != '.')
            c = c - 32;
        if (is_letter(c) != 1)
            c = '_';
        new[i] = c;
    }
    new[i] = '\0';
    //printf("Define = %s\n", new);
    return (new);
}

char *cpp_formater(char *path)
{
    char *form = malloc(sizeof(char) * (strlen(path) + 1));

    if (form == NULL)
        return (NULL);
    for (int i = 0; path[i]; i++) {
        if (i == 0 && path[i] <= 'z' && path[i] >= 'a')
            form[i] = path[i] - 32;
        else
            form[i] = path[i];
        form[i + 1] = '\0';
    }
    return (form);
}
