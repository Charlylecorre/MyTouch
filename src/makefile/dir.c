/*
** EPITECH PROJECT, 2022
** dir.c
** File description:
** dir
*/

#include "my_touch.h"

char **get_dir_list(char *path, int search)
{
    int size = dir_len(path, search);
    char **list = malloc(sizeof(char *) * (size + 1));
    DIR *dir;
    struct dirent *sd;
    struct stat file;
    int i = 0;

    if (list == NULL)
        return (NULL);
    if ((dir = opendir(path)) == NULL || stat(path, &file) != 0)
        return (NULL);
    while ((sd = readdir(dir)) != NULL) {
        if (search == ONLY_DIR && opendir(sd->d_name) != NULL
            && strcmp(sd->d_name, "..") != 0 && strcmp(sd->d_name, ".") != 0) {
            list[i++] = strdup(sd->d_name);
        }
        if (search == ONLY_FILE && opendir(sd->d_name) == NULL
            && strcmp(sd->d_name, "..") != 0 && strcmp(sd->d_name, ".") != 0) {
            list[i++] = strdup(sd->d_name);
        }
        if (search == ALL && strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0)
            list[i++] = strdup(sd->d_name);
    }
    list[i] = NULL;
    closedir(dir);
    return (list);
}

int dir_len(char *path, int search)
{
    DIR *dir;
    struct dirent *sd;
    struct stat file;
    int len = 0;

    if ((dir = opendir(path)) == NULL || stat(path, &file) != 0)
        return (0);
    while ((sd = readdir(dir)) != NULL) {
        if (search == ONLY_DIR && opendir(sd->d_name) != NULL
            && strcmp(sd->d_name, "..") != 0 && strcmp(sd->d_name, ".") != 0) {
            len++;
            //printf("Dir: %s\n", sd->d_name);
        }
        if (search == ONLY_FILE && opendir(sd->d_name) == NULL
            && strcmp(sd->d_name, "..") != 0 && strcmp(sd->d_name, ".") != 0) {
            len++;
            //printf("File: %s\n", sd->d_name);
        }
        if (search == ALL && strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0)
            len++;
    }
    closedir(dir);
    return (len);
}