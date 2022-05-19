/*
** EPITECH PROJECT, 2022
** makefile builder.c
** File description:
** makefile builder
*/

#include "my_touch.h"

char **ext_filter(char **list, int type)
{
    int final_len = 0;
    char **final_list = NULL;
    int index = 0;

    for (int i = 0; list[i]; i++)
        if (find_type(list[i]) == type)
            final_len++;
    printf("len = %i\n", final_len);
    if ((final_list = malloc(sizeof(char *) * (final_len + 1))) == NULL)
        return (NULL);
    for (int i = 0; list[i]; i++)
        if (find_type(list[i]) == type && (final_list[index++] = strdup(list[i])) == NULL)
            return (NULL);
    final_list[index] = NULL;
    free_array(list);
    return (final_list);
}

int makefile_builder()
{
    char **dir_list = get_dir_list(".", ONLY_DIR);
    char **file_list = get_dir_list(".", ONLY_FILE);

    file_list = ext_filter(file_list, C);
    if (file_list == NULL)
        return (error_message("Error: Allocation failed!\n"));
    printf("Dir_list:\n");
    display_list(dir_list);
    printf("File_list:\n");
    display_list(file_list);
    free_array(file_list);
    free_array(dir_list);
    return (0);
}