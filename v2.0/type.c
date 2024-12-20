/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include "../shell/shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


static int new_type(char **str, int x,  struct usr_s *usr)
{
    char path[100];

    sprintf(path, "%s%s", usr->path, str[x]);
    if (dir_exists(path) == 0) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, "\033[1m\033[32m%s\033[0m already exist\n\n", str[x]);
    }

    else {
        create_dir(path, 0);
        dprintf(1, "Type \033[1m\033[33m\"%s\"\033[0m successfully ", str[x]);
        dprintf(1, "\033[1m\033[32mcreated\033[0m\n");
    }
    if (str[x + 1] != NULL)
        return add_type(str, x + 1, usr);
    return SUCCESS;
}

int add_type(char **str, int x, struct usr_s *usr)
{
    if (str[x] == NULL)
        return SUCCESS;
    return new_type(str, x, usr);
}

int type(char **str, struct data_s **data, struct usr_s *usr)
{
    int x = 1;

    if (str[1] == NULL) {
        help_type();
        return 0;
    }
    if (data == NULL)
        x = 1;
    return add_type(str, x, usr);
}