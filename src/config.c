/*
** EPITECH PROJECT, 2022
** config.c
** File description:
** config
*/

#include "my_touch.h"

char *get_config_name(char *av)
{
    int start = strlen("-name:");
    char *name = NULL;

    if (strncmp(av, "-name:", start) != 0)
        return (NULL);
    name = strdup(&av[start]);
    return (name);
}

int free_config(config_t *config)
{
    if (config->project_name != NULL)
        free(config->project_name);
    config->project_name = NULL;
    return (0);
}

config_t *init_config(char **av)
{
    config_t *config = malloc(sizeof(config_t));
    config->project_name = NULL;
    config->debug_mode = false;

    for (int i = 0; av[i] != NULL && config->project_name == NULL; i++) {
        if (strstr(av[i], "-name:") != NULL) {
            config->project_name = get_config_name(av[i]);
            if (config->project_name == NULL)
                return (NULL);
        }
        if (strcmp(av[i], "-debug") == 0) {
            config->debug_mode = true;
        }
    }
    return config;
}