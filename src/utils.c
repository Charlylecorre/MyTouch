/*
** EPITECH PROJECT, 2022
** utils.c
** File description:
** utils
*/

#include "my_touch.h"

int multi_cmp(int nb, char *str, ...)
{
    va_list multi_str;
    va_start(multi_str, str);
    char *local;

    for (int i = 0; i < nb; i++) {
        local = (char *) va_arg(multi_str, char *);
        if (strcmp(str, local) == 0) {
            va_end(multi_str);
            return (1);
        }
    }
    va_end(multi_str);
    return (0);
}

int find_array_size(char *buff, char stop)
{
    int size = 0;

    for (int i = 0; buff[i]; i++)
        if (buff[i] == stop)
            size++;
    return (size + 1);
}

int find_next_len(char *str, char stop)
{
    int len = 0;

    for (;str[len] && str[len] != stop; len++);
    return (len);
}

char *next_str(char *str, char stop, int next_len)
{
    char *next_str = malloc(sizeof(char) * (next_len + 1));
    int i = 0;

    if (next_str == NULL)
        return (NULL);
    for (; str[i] && str[i] != stop; i++)
        next_str[i] = str[i];
    next_str[i] = '\0';
    return (next_str);
}

char **str_to_word_array(char *str, char stop)
{
    char **array = NULL;
    int size = find_array_size(str, stop);
    int next_len = 0;
    int j = 0;

    if (str == NULL)
        return (NULL);
    if ((array = malloc(sizeof(char *) * (size + 1))) == NULL)
        return (NULL);
    for (int i = 0; str[i];) {
        next_len = find_next_len(&str[i], stop);
        if (next_len != 0) {
            array[j] = next_str(&str[i], stop, next_len);
            array[j + 1] = NULL;
            if (array[j] == NULL) {
                free_array(array);
                return (NULL);
            }
            j++;
        }
        i += next_len;
        if (str[i] == stop)
            i++;
    }
    return (array);
}

char **add_to_arrayV2(char **array, char *str)
{
    int size = array_size(array);
    char **new_array = malloc(sizeof(char *) * (size + 2));
    int i = 0;

    if (new_array == NULL)
        return (NULL);
    for (; array[i]; i++) {
        new_array[i] = strdup(array[i]);
    }
    new_array[i] = strdup(str);
    new_array[i + 1] = NULL;
    free_array(array);
    return (new_array);
}

char **add_to_array(char **array, char *str)
{
    int size = array_size(array);

    array = realloc(array, sizeof(char *) * (size + 2));
    if (array == NULL || (array[size] = strdup(str)) == NULL)
        return (NULL);
    array[size + 1] = NULL;
    //display_list("ADD ARRAY", array);
    return (array);
}

char **concat_array(char **libs, char **tmp_list)
{
    int i = array_size(libs);
    int add = array_size(tmp_list);
    int size = i + add;

    if (tmp_list == NULL)
        return (0);
    libs = realloc(libs, sizeof(char *) * (size + 1));
    if (libs == NULL)
        return (NULL);
    for (int j = 0; tmp_list[j]; j++, i++) {
        libs[i] = strdup(tmp_list[j]);
        libs[i + 1] = NULL;
    }
    return (libs);
}

int array_size(char **av)
{
    int len = 0;

    for (; av && av[len]; len++);
    return (len);
}

int is_banned_dir(char *path)
{
    if (strcmp(path, ".") == 0 || strcmp(path, "..") == 0 || strcmp(path, "tests") == 0
        || strcmp(path, "bonus") == 0 || strcmp(path, "lib") == 0)
        return (-1);
    if (strcmp(path, ".idea") == 0 || strcmp(path, ".git") == 0
        || strcmp(path, "cmake-build-debug") == 0)
        return (-1);
    return (0);
}

void display_list(char *msg, char **av)
{
    int i = 0;

    printf(PIN"Display list ["CYN"%s"PIN"]\n"NC, msg);
    if (av == NULL)
        printf(RED"List : NULL\n"NC);
    for (; av && av[i]; i++)
        printf(YEL"av[%i]:" CYN" %s\n" NC, i, av[i]);
    if (av && av[i] == NULL)
        printf(YEL"av[%i]:" RED" NULL\n" NC, i);
}

int search_av(char **av, char *str)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (strcmp(av[i], str) == 0)
            return (1);
    }
    return (0);
}

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

    if (strncmp(path, "Makefile", strlen("Makefile")) == 0)
        return (2);
    for (; path[i]; i++);
    for (; i > 0 && path[i] != '.'; i--);
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

void free_array(char **av)
{
    for (int i= 0; av && av[i]; i++)
        free(av[i]);
    if (av)
        free(av);
}