/*
** EPITECH PROJECT, 2022
** my touch.h
** File description:
** my touch
*/

#ifndef MY_TOUCH_H
    #define MY_TOUCH_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <ncurses.h>
#include <stdbool.h>
#include "color.h"

#define NOTYPE -1
#define C 0
#define H 1
#define MAKEFILE 2
#define PYTHON 3
#define SH 4
#define CPP 5
#define HPP 6
#define ONLY_DIR 1
#define ONLY_FILE 2
#define ALL 3

typedef struct config {
    bool debug_mode;
    char *project_name;
} config_t;

//config.c
config_t *init_config(char **av);
int free_config(config_t *config);

//build.c
char *build_hpp_link(char **arg);
char *build_path(char *file, char *ext);
char *build_file_name(char *path, int type);

//create_file.c
int create_file(char *path, int type, char **arg, int replace, config_t *config);

//file_engine.c
int file_engine(char *av, int replace, config_t *config);

//formater.c
char *define_formateur(char *define);
char *cpp_formater(char *path);


    //Makefile
        //getlib
        //getlib.c
        char **getlib(char **src, char **include, config_t *config);

    //dir.c
    char **add_to_file_list(char **list, char **add_list);
    char **get_dir_list(char *path, int search);
    int dir_len(char *path, int search);
    char **recup_file_in_dir(char *path, int type);

    //makefile_builder.c
    int makefile_builder(int fd, int an, char **ext, config_t *config);
    char **ext_filter(char **list, int type);

//my_touch.c
void make_python(int fd);
void make_makefile(char *makefile, int fd, int an);
int do_hpp(char *project, char **arg, int fd, char *path);
int do_cpp(char **arg, int fd);
int print_header(int fd, char *path, int type, char **arg, config_t *config);

//parser.c
int parser_len(char **arg);
int next_len(char *line);
char *next_ext(char *line);
int count_ext(char *line);
char *remove_ext(char *av);
char **parser(char *av);
void display_parser(char **parser);
void free_parser(char **parser);

//project_name.c
char *get_project_name(char *path);

//utils.c
int strstart(char *str, char *start);
int multi_strstr(int nb, char *str, ...);
int super_strstr(int nb, char *str, ...);
int super_cmp(int nb, char *str, ...);
int multi_cmp(int nb, char *str, ...);
char **str_to_word_array(char *str, char stop);
char **concat_array(char **libs, char **tmp_list);
char **add_to_arrayV2(char **array, char *str);
char **add_to_array(char **array, char *str);
int replace_mod(char **av);
int find_type(char *path);
int arg_conatain(char **arg, char *src);
int display_help(void);
int is_letter(char c);
int error_message(char *msg);
void display_list(char *msg, char **av);
void free_array(char **av);
int is_banned_dir(char *path);
int array_size(char **av);

#endif //MY_TOUCH_H
