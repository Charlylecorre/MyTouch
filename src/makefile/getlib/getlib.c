/*
** EPITECH PROJECT, 2022
** getlib.c
** File description:
** getlib
*/

#include "my_touch.h"

char *find_lib(char *line)
{
    char *lib = NULL;
    char *csfml[8] = {"<SFML/Window.h>", "<SFML/Audio.h>", "<SFML/Graphics/RenderWindow.h>", "<SFML/Config.h>", "<SFML/System.h>", "<SFML/Graphics/Export.h>", "<SFML/Graphics.h>", NULL};
    char *csfml_ref = "-lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-audio";
    char *simple[4] = {"<ncurses.h>", "<math.h>", "<pthread.h>", NULL};
    char *simple_ref[4] = {"-lncurses", "-lm", "-lpthread", NULL};
    char *sfml[2] = {"#include <SFML/Graphics.hpp>", NULL};
    char *sfml_ref = "-lsfml-window -lsfml-graphics -lsfml-system";

    for (int i = 0; csfml[i]; i++) {
        if (strstr(line, "#include") != NULL && strstr(line, csfml[i]) != NULL) {
            lib = strdup(csfml_ref);
            return (lib);
        }
    }

    for (int i = 0; sfml[i]; i++) {
        if (strstr(line, "#include") != NULL && strstr(line, sfml[i]) != NULL) {
            lib = strdup(sfml_ref);
            return (lib);
        }
    }

    for (int i = 0; simple[i]; i++) {
        if (strstr(line, "#include") != NULL && strstr(line, simple[i]) != NULL) {
            lib = strdup(simple_ref[i]);
            return (lib);
        }
    }
    return (lib);
}

char **get_file_lib(char *path)
{
    char **libs = NULL;
    char *buff = NULL;
    struct stat file;
    char **array = NULL;
    char *line_lib = NULL;
    int fd;

    if (stat(path, &file) == -1 || (libs = malloc(sizeof(char *) * (1))) == NULL
        || (fd = open(path, O_RDONLY)) == -1
        || (buff = malloc(sizeof(char) * (file.st_size + 1))) == NULL)
        return (NULL);
    read(fd, buff, file.st_size);
    buff[file.st_size] = '\0';
    close(fd);
    libs[0] = NULL;
    array = str_to_word_array(buff, '\n');
    free(buff);

    for (int i = 0; array[i]; i++) {
        line_lib = find_lib(array[i]);
        if (line_lib != NULL) {
            libs = add_to_array(libs, line_lib);
            free(line_lib);
            line_lib = NULL;
        }
    }
    free_array(array);
    return (libs);
}

char **getlib(char **src, char **include)
{
    char **libs = NULL;
    char **tmp_list = NULL;

    if ((libs = malloc(sizeof(char *) * (1))) == NULL)
        return (NULL);
    libs[0] = NULL;

    for (int i = 0; src[i]; i++) {
        tmp_list = get_file_lib(src[i]);
        if (tmp_list[0] != NULL && (libs = concat_array(libs, tmp_list)) == NULL)
            return (NULL);
        free_array(tmp_list);
        tmp_list = NULL;
        //printf(GRN"+1 : %s\n", src[i]);
    }

    for (int i = 0; include[i]; i++) {
        tmp_list = get_file_lib(include[i]);
        if ((libs = concat_array(libs, tmp_list)) == NULL)
            return (NULL);
        free_array(tmp_list);
        tmp_list = NULL;
        //printf(GRN"+1 : %s\n", include[i]);
    }

    return (libs);
}
