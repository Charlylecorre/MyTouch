/*
** EPITECH PROJECT, 2022
** dir.c
** File description:
** dir
*/

#include "my_touch.h"

char *create_link_file(char *path, char *name)
{
    int len = strlen(name);
    char *link = NULL;

    if (strcmp(path, ".") != 0)
        len += strlen(path) + 1;
    link = malloc(sizeof (char) * (len + 1));
    if (link == NULL)
        return (NULL);
    if (strcmp(path, ".") != 0) {
        strcpy(link, path);
        strcat(link, "/");
    } else {
        strcpy(link, "");
    }
    strcat(link, name);
    return (link);
}

char **get_dir_list(char *path, int search)
{
    int size = dir_len(path, search);
    char **list = malloc(sizeof(char *) * (size + 1));
    DIR *dir;
    struct dirent *sd;
    struct stat file;
    int i = 0;
    char *local_link = NULL;
    struct stat local_file;


    if (list == NULL)
        return (NULL);
    if ((dir = opendir(path)) == NULL || stat(path, &file) != 0)
        return (NULL);
    while ((sd = readdir(dir)) != NULL) {
        local_link = create_link_file(path, sd->d_name);
        stat(local_link, &local_file);
        if (search == ONLY_DIR && S_ISDIR(local_file.st_mode)
            && is_banned_dir(sd->d_name) == 0) {
            list[i++] = create_link_file(path, sd->d_name);
        }
        if (search == ONLY_FILE && !S_ISDIR(local_file.st_mode)
            && is_banned_dir(sd->d_name) == 0) {
            list[i++] = create_link_file(path, sd->d_name);
        }
        if (search == ALL && is_banned_dir(sd->d_name) == 0)
            list[i++] = create_link_file(path, sd->d_name);
        free(local_link);
    }
    list[i] = NULL;
    closedir(dir);
    free(sd);
    return (list);
}

int dir_len(char *path, int search)
{
    DIR *dir;
    struct dirent *sd;
    struct stat file;
    struct stat local_file;
    int len = 0;
    char *local_link = NULL;

    if ((dir = opendir(path)) == NULL || stat(path, &file) != 0)
        return (0);
    while ((sd = readdir(dir)) != NULL) {
        local_link = create_link_file(path, sd->d_name);
        stat(local_link, &local_file);
        if (search == ONLY_DIR && S_ISDIR(local_file.st_mode)
            && is_banned_dir(sd->d_name) == 0) {
            len++;
            //printf("Dir: %s\n", sd->d_name);
        }
        if (search == ONLY_FILE && !S_ISDIR(local_file.st_mode)
            && is_banned_dir(sd->d_name) == 0) {
            len++;
            //printf("File: %s\n", sd->d_name);
        }
        if (search == ALL && is_banned_dir(sd->d_name) == 0)
            len++;
        free(local_link);
    }
    closedir(dir);
    free(sd);
    return (len);
}

char **add_to_file_list(char **list, char **add_list)
{
    int size = array_size(list) + array_size(add_list) + 1;
    char **new_list = malloc(sizeof (char *) * (size));
    int index = 0;

    if (new_list == NULL)
        return (NULL);
    for (int i = 0; list && list[i]; i++, index++)
        new_list[index] = strdup(list[i]);
    for (int i = 0; add_list && add_list[i]; i++, index++)
        new_list[index] = strdup(add_list[i]);
    new_list[index] = NULL;
    free_array(list);
    free_array(add_list);
    return (new_list);
}

char *build_next_dir(char *path, char *next)
{
    int len = strlen(next);
    char *next_dir = NULL;

    if (strcmp(path, ".") != 0)
        len += strlen(path) + 1;
    next_dir = malloc(sizeof (char) * (len + 1));
    if (next_dir == NULL)
        return (NULL);
    if (strcmp(path, ".") != 0) {
        strcpy(next_dir, path);
        strcat(next_dir, "/");
    } else {
        strcpy(next_dir, "");
    }
    strcat(next_dir, next);
    return (next_dir);
}

char **recup_file_in_dir(char *path, int type)
{
    char **file_here = get_dir_list(path, ONLY_FILE);
    char **other_path = get_dir_list(path, ONLY_DIR);

//    printf("----[%s]-----\n", path);
//    display_list("FILE", file_here);
//    display_list("DIR", other_path);
//    printf("--------------\n\n");
    if (file_here == NULL || other_path == NULL)
        return (NULL);
    file_here = ext_filter(file_here, type);
    for (int i = 0; other_path[i]; i++) {
        file_here = add_to_file_list(file_here, recup_file_in_dir(other_path[i], type));
    }
    free_array(other_path);
    //display_list(path, file_here);
    return (file_here);
}