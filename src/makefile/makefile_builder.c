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
    if ((final_list = malloc(sizeof(char *) * (final_len + 1))) == NULL)
        return (NULL);
    for (int i = 0; list[i]; i++)
        if (find_type(list[i]) == type && (final_list[index++] = strdup(list[i])) == NULL)
            return (NULL);
    final_list[index] = NULL;
    free_array(list);
    return (final_list);
}

int find_makefile_type(char *makefile)
{
    int type[2] = {C, CPP};
    char *ref_type[2] = {".c", ".cpp"};
    int i = 0;

    for (; makefile[i] && makefile[i] != '.'; i++);
    for (int j = 0; j < 2; j++) {
        if (strcmp(&makefile[i], ref_type[j]) == 0)
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

int print_makefile(char *name, int fd, int an, char **src, int type)
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

    for (int i = 0; src && src[i]; i++) {
        if (i == 0)
            dprintf(fd, "SRC = \t%s\t\\\n", src[i]);
        dprintf(fd, "\t%s\t\\\n", src[i]);
    }
    dprintf(fd, "\n");

    dprintf(fd, "OBJ = 	$(SRC:.%s=.o)\n\n", str_type);
    dprintf(fd, "CFLAGS = -I include -W -Wall -Wextra\n\n");
    dprintf(fd, "all:	$(NAME)\n\n");
    dprintf(fd, "$(NAME) : $(OBJ)\n");
    if (type == C)
        dprintf(fd, "	gcc -o $(NAME) $(OBJ) $(CFLAGS)\n\n");
    if (type == CPP)
        dprintf(fd, "	g++ -o $(NAME) $(OBJ) $(CFLAGS)\n\n");
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

int makefile_builder(char *makefile, int fd, int an)
{
    int type = find_makefile_type(makefile);
    char *project_name = find_makefile_project_name();
    char **file_list = recup_file_in_dir(".", type);

    if (project_name == NULL || file_list == NULL)
        return (error_message("Error: Allocation failed!\n"));
//    printf(CYN"Name = %s\n" NC, project_name);
//    printf(RED"Type = %i\n"NC, type);
//    printf("File_list:\n");
//    display_list(file_list);

    print_makefile(project_name, fd, an, file_list, type);

    free(project_name);
    free_array(file_list);
    return (0);
}