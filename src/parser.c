/*
** EPITECH PROJECT, 2022
** parser.c
** File description:
** parser
*/

#include "my_touch.h"

int parser_len(char **arg)
{
    int i = 0;

    for (; arg[i]; i++);
    return (i);
}

int next_len(char *line)
{
    int len = 0;

    for (; line[len] && line[len] != '/'; len++);
    return (len);
}

char *next_ext(char *line)
{
    int len = next_len(line);
    char *next = malloc(sizeof(char) * (len + 1));
    int i = 0;

    for (; line[i] && line[i] != '/'; i++)
        next[i] = line[i];
    next[i] = '\0';
    return (next);
}

int count_ext(char *line)
{
    char *next = strstr(line, ".");
    int count = 0;

    if (line[0] != '\0' && line[0] != '.')
        count++;
    for (; next != NULL; next = strstr(&next[1], "/"), count++);
    return (count);
}

char *remove_ext(char *av)
{
    char *str = NULL;
    int len = 0;

    for (; av[len] && av[len] != '.'; len++);
    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return (NULL);
    for (int i = 0; av[i] && av[i] != '.'; i++) {
        str[i] = av[i];
        str[i + 1] = '\0';
    }
    return (str);
}

char **parser(char *av)
{
    int len = count_ext(av);
    char *next = strstr(av, ".");
    char **parser = malloc(sizeof(char *) * (len + 1));
    int i = 0;

    parser[i++] = remove_ext(av);
    for (; next != NULL; next = strstr(&next[1], "/"), i++) {
        parser[i] = next_ext(&next[1]);
    }
    parser[i] = NULL;
    return (parser);
}

void display_parser(char **parser)
{
    int i = 0;

    for (; parser[i]; i++)
        printf(CYN "parser[%i]: %s\n", i, parser[i]);
    if (parser[i] == NULL)
        printf(CYN "parser[%i]: NULL\n", i);
}

void free_parser(char **parser)
{
    for (int i = 0; parser && parser[i]; i++)
        free(parser[i]);
    if (parser)
        free(parser);
}
