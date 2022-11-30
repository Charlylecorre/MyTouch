/*
** EPITECH PROJECT, 2022
** create_file.c
** File description:
** create file
*/

#include "my_touch.h"

int create_file(char *path, int type, char **arg, int replace, int debug_mode)
{
    int file;
    char *file_name = build_file_name(path, type);
    char *type_equal[] = {".c", ".h", "Makefile", "Python", ".sh", ".cpp", ".hpp"};

    if (type != PYTHON && type != SH)
        file = open(file_name, O_CREAT | O_RDWR | replace, 0664);
    if (type == PYTHON || type == SH)
        file = open(file_name, O_CREAT | O_RDWR | replace, 0755);
    if (file == -1) {
        free(file_name);
        return (-1);
    }
    printf(GRN "Create file : \'%s\'"NC, file_name);
    if (type != NOTYPE)
        printf(YEL "\ttype : %s\n" NC, type_equal[type]);
    else
        printf("\n");
    if (type != NOTYPE && print_header(file, file_name, type, arg, debug_mode) != 0) {
        free(file_name);
        close(file);
        return (error_message("Error : Header fail\n"));
    }
    free(file_name);
    close(file);
    return (0);
}