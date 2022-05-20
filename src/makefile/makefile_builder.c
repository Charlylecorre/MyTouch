/*
** EPITECH PROJECT, 2022
** makefile builder.c
** File description:
** makefile builder
*/

#include "my_touch.h"

char *only_dir(char *list)
{
    int len = strlen(list);
    char *dir = NULL;

    for (; len > 0 && list[len - 1] != '/'; len--);
    dir = malloc(sizeof (char) * (len + 1));
    if (dir == NULL)
        return (NULL);
    for (int i = 0; i < len; i++) {
        dir[i] = list[i];
        dir[i + 1] = '\0';
    }
    return (dir);
}

int count_dir_var(char **list)
{
    int size = 0;

    for (int i = 0; list && list[i]; i++) {
        if (strcmp(list[i], "") != 0)
            size++;
    }
    return (size);
}

char **remove_doublon(char **list)
{
    int size = 0;
    char **new_list = NULL;
    int index = 0;

    for (int i = 0; list && list[i]; i++) {
        for (int j = i; list && list[j]; j++) {
            if (j != i && strcmp(list[i], list[j]) == 0) {
                free(list[j]);
                list[j] = strdup("");
            }
        }
    }
    size = count_dir_var(list);
    new_list = malloc(sizeof (char *) * (size + 1));
    if (new_list == NULL)
        return (NULL);
    for (int i = 0; list && list[i]; i++) {
        if (strcmp(list[i], "") != 0) {
            new_list[index++] = strdup(list[i]);
        }
    }
    new_list[index] = NULL;
    free_array(list);
    return (new_list);
}

char **dir_filter(char **list)
{
    int size = array_size(list);
    char **filter = malloc(sizeof (char *) * (size + 1));

    if (filter == NULL)
        return (NULL);
    for (int i = 0; list && list[i]; i++) {
        filter[i] = only_dir(list[i]);
    }
    free_array(list);
    return (filter);
}

char **ext_filter(char **list, int type)
{
    int final_len = 0;
    char **final_list = NULL;
    int index = 0;

    for (int i = 0; list[i]; i++)
        if (find_type(list[i]) == type)
            final_len++;
    if ((final_list = malloc(sizeof(char *) * (final_len + 1))) == NULL)
        return (NULL);
    for (int i = 0; list[i]; i++)
        if (find_type(list[i]) == type && (final_list[index++] = strdup(list[i])) == NULL)
            return (NULL);
    final_list[index] = NULL;
    free_array(list);
    return (final_list);
}

int find_makefile_type(char **ext)
{
    int type[2] = {C, CPP};
    char *ref_type[2] = {"c", "cpp"};

    if (ext[1] == NULL)
        return (C);
    for (int j = 0; j < 2; j++) {
        if (strcmp(ext[1], ref_type[j]) == 0)
            return (type[j]);
    }
    return (C);
}

char *find_makefile_project_name()
{
    size_t size = PATH_MAX;
    char *pwd = malloc(sizeof(char) * (size + 1));
    char *name = NULL;
    int len = 0;
    int j = 0;
    int i;

    if (pwd == NULL)
        return (NULL);
    getcwd(pwd, size);
    for (i = strlen(pwd); i > 0 && pwd[i - 1] != '/'; i--, len++);
    name = malloc(sizeof (char) * (len + 1));
    if (name == NULL) {
        free(pwd);
        return (NULL);
    }
    for (; pwd[i]; i++, j++)
        name[j] = pwd[i];
    name[j] = '\0';
    free(pwd);
    return (name);
}

char *type_to_str(int type)
{
    int types[2] = {C, CPP};
    char *type_ref[2] = {"c", "cpp"};
    char *str = NULL;
    int len = 0;

    for (int j = 0; j < 2; j++) {
        if (type == types[j]) {
            len = strlen(type_ref[j]) + 1;
            str = malloc(sizeof(char) * (len));
            strcpy(str, type_ref[j]);
            return (str);
        }
    }
    return (NULL);
}

int print_makefile(char *name, int fd, int an, char **src, char **hpp, int type)
{
    char *str_type = type_to_str(type);

    if (str_type == NULL)
        return (error_message("Error: Makefile type not found!\n"));

    dprintf(fd, "##\n");
    dprintf(fd, "## EPITECH PROJECT, %i\n", an);
    dprintf(fd, "## MAKEFILE\n");
    dprintf(fd, "## File description:\n");
    dprintf(fd, "## Makefile\n");
    dprintf(fd, "##\n\n");
    dprintf(fd, "NAME = %s\n\n", name);

    if (src == NULL || src[0] == NULL)
        dprintf(fd, "SRC =\n");
    for (int i = 0; src && src[i]; i++) {
        if (i == 0)
            dprintf(fd, "SRC =\t%s\t\\\n", src[i]);
        else
            dprintf(fd, "     \t%s\t\\\n", src[i]);
    }
    dprintf(fd, "\n");

    dprintf(fd, "OBJ = 	$(SRC:.%s=.o)\n\n", str_type);
    if (type == C)
        dprintf(fd, "CFLAGS = -I include -W -Wall -Wextra\n\n");
    if (type == CPP) {
        dprintf(fd, "CXXFLAGS += ");
        for (int i = 0; hpp && hpp[i]; i++) {
            dprintf(fd, "-I %s ", hpp[i]);
        }
        dprintf(fd, "-std=c++20 -W -Wall -Wextra\n\n");
    }
    dprintf(fd, "LIBS =	\n\n");
    dprintf(fd, "all:	$(NAME)\n\n");
    dprintf(fd, "$(NAME) : $(OBJ)\n");
    if (type == C)
        dprintf(fd, "	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)\n\n");
    if (type == CPP)
        dprintf(fd, "	g++ -o $(NAME) $(OBJ) $(LIBS)\n\n");
    dprintf(fd, "clean:\n");
    dprintf(fd, "	rm -f $(OBJ)\n");
    dprintf(fd, "	rm -f *~\n");
    dprintf(fd, "	rm -f vgcore.*\n");
    dprintf(fd, "	rm -f Test\n\n");
    dprintf(fd, "fclean: clean\n");
    dprintf(fd, "	rm -f $(NAME)\n\n");
    dprintf(fd, "re:	fclean all\n\n");
    dprintf(fd, "valgrind : fclean\n");
    dprintf(fd, "	gcc -o $(NAME) $(SRC) $(CFLAGS) -g\n\n");
    dprintf(fd, "## Makefile generate by MyTouch : @charly.le-corre\n");

    free(str_type);
    return (0);
}

int makefile_builder(int fd, int an, char **ext)
{
    int type = find_makefile_type(ext);
    char *project_name = find_makefile_project_name();
    char **file_list = recup_file_in_dir(".", type);
    char **hpp_list = recup_file_in_dir(".", HPP);

    if (project_name == NULL || file_list == NULL || hpp_list == NULL)
        return (error_message("Error: Allocation failed!\n"));
    if ((hpp_list = dir_filter(hpp_list)) == NULL || (hpp_list = remove_doublon(hpp_list)) == NULL)
        return (error_message("Error: Allocation failed!\n"));
    print_makefile(project_name, fd, an, file_list, hpp_list, type);
    printf(RED"⚠️ " RED" Libs are not generate by the AutoMakefile generator!\n"NC);
    free(project_name);
    free_array(hpp_list);
    free_array(file_list);
    return (0);
}