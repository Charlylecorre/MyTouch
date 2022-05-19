/*
** EPITECH PROJECT, 2022
** my touch.h
** File description:
** my touch
*/

#ifndef MY_TOUCH_H
    #define MY_TOUCH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "color.h"

#define NOTYPE -1
#define C 0
#define H 1
#define MAKEFILE 2
#define PYTHON 3
#define SH 4
#define CPP 5
#define HPP 6

//build.c
char *build_hpp_link(char **arg);
char *build_path(char *file, char *ext);
char *build_file_name(char *path, int type);

//create_file.c
int create_file(char *path, int type, char **arg, int replace);

//file_engine.c
int file_engine(char *av, int replace);

//formater.c
char *define_formateur(char *define);
char *cpp_formater(char *path);

//makefile_builder.c

//my_touch.c
void make_python(int fd);
void make_makefile(int fd, int an);
int do_hpp(char *project, char **arg, int fd, char *path);
int do_cpp(char **arg, int fd);
int print_header(int fd, char *path, int type, char **arg);
int create_file(char *path, int type, char **arg, int replace);

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
int replace_mod(char **av);
int find_type(char *path);
int arg_conatain(char **arg, char *src);
int display_help(void);
int is_letter(char c);
int error_message(char *msg);

#endif //MY_TOUCH_H
