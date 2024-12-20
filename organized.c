/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "include/my.h"
#include "include/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int search_flag(char *str, struct data_s **data, struct usr_s *usr)
{
    char **list = cut(str);

    if (list == NULL)
        return ERROR_INT;
    for (int i = 0; flag_long[i].flag != NULL; i++) {
        if (my_strcmp(list[0], flag_long[i].flag) == 0) {
            flag_long[i].func(list, data, usr);
            return SUCCESS;
        }
    }
    dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
    dprintf(1, "\"%s", list[0]);
    my_putstr("\" does not exist\n");
    dprintf(1, "\033[1m\033[33m[HACK]\033[0m Try to use the command ");
    dprintf(1, "\033[1m\033[38;5;214m\"help\"\033[0m\n\n");
    free_strstr(list);
    return ERROR_INT;
}

static void free_struct(struct data_s *data)
{
    if (data == NULL)
        return;
    if (data->next != NULL)
        free_struct(data->next);
    if (data->tag != NULL)
        free(data->tag);
    if (data->name != NULL)
        free(data->name);
    if (data->path != NULL)
        free(data->path);
    free(data);
}

static int error_case(struct data_s *data, struct usr_s *usr)
{
    return run_organized(usr, data);
}

int run_organized(struct usr_s *usr, struct data_s *data)
{
    char *str = NULL;

    all_dir(usr->path);
    dprintf(1, "\033[35m[%s]\033[0m", usr->usr);
    my_putstr("-> ");
    str = get_line();
    if (str == NULL) {
        free_struct(data);
        free_usr(usr);
        return ERROR_INT;
    }
    if (my_strcmp("exit", str) == 0) {
        free(str);
        free_struct(data);
        free_usr(usr);
        return SUCCESS;
    }
    search_flag(str, &data, usr);
    free(str);
    return error_case(data, usr);
}

int comands(char const *str)
{
    if (my_strcmp(str, "-h") == 0) {
        my_putstr("organize data\n");
        return EXIT_SUCCESS;
    }
    my_dputstr(2, "flag '");
    my_dputstr(2, str);
    my_dputstr(2, "' does not exist\n");
    return EXIT_ERROR;
}

static int log_or_create(char *path)
{
    char *nb = NULL;

    dprintf(1, "\033[35m[~]\033[0m");
    my_putstr("-> ");
    nb = get_line();
    if (my_strcmp(nb, "1") == 0)
        return loggin(path);
    if (my_strcmp(nb, "2") == 0)
        return create_usr(path);
    dprintf(1, "\n\033[1m\033[31m[ERROR]\033[0m  \033[31mInvalid Answer\033[0m\n");
    dprintf(1, "To \033[1m\033[32mlogin\033[0m ");
    dprintf(1, "type \033[1m\033[32m1\033[0m ");
    dprintf(1, "and to \033[1m\033[34mcreate a new user\033[0m ");
    dprintf(1, "type \033[1m\033[34m2\033[0m\n\n");
    return log_or_create(path);
}

int organized(int const ac, char const **av)
{
    char *path = NULL;

    if (ac > 1)
        return comands(av[1]);
    path = get_def_file();
    if (dir_exists(path) == FAIL)
        create_def_files();
    dprintf(1, "Welcome back\n");
    dprintf(1, "Do you want to login or create a user?\n");
    dprintf(1, "To \033[1m\033[32mlogin\033[0m ");
    dprintf(1, "type \033[1m\033[32m1\033[0m ");
    dprintf(1, "and to \033[1m\033[34mcreate a new user\033[0m ");
    dprintf(1, "type \033[1m\033[34m2\033[0m\n");
    return log_or_create(path);
}
