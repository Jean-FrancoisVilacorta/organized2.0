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
#include <dirent.h>
#include <stdio.h>
#include <stdio.h>

int is_empty(const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *info;

    if (dir == NULL) {
        return FAIL;
    }
    while ((info = readdir(dir)) != NULL) {
        if (info->d_name[0] != '.') {
            return 1;
        }
    }
    return SUCCESS;
}

void remove_not_empty(const char *path)
{
    char str[200];
    sprintf(str, "rm -rf %s", path);
    system(str);
}

int not_empty(char **str, int x, struct usr_s *usr, char *path)
{
    dprintf(1, "\033[1m\033[33m[Warning]\033[0m");
    dprintf(1, "This \033[1m\033[33m\"TYPE\"\033[0m is not empty!\n");
    dprintf(1, "Are you sure you want to remove it? [N/Y]\n");
    dprintf(1, "\033[35m[%s]\033[0m", usr->usr);
    my_putstr("-> ");
    if (yes_or_not() == SUCCESS) {
        remove_not_empty(path);
        dprintf(1, "Type \033[1m\033[33m\"%s\"\033[0m successfully ", str[x]);
        dprintf(1, "\033[1m\033[31mdeleted\033[0m\n");
    } else
        dprintf(1, "Failure to delete\n");
    if (str[x + 1] != NULL)
        return search_des(str, x + 1, usr);
    return SUCCESS;
}

int destroy_dir(char **str, int x, struct usr_s *usr)
{
    char path[100];

    sprintf(path, "%s%s", usr->path, str[x]);
    if (dir_exists(path) != 0) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, "\033[1m\033[33m\"%s\"\033[0m does not exist\n\n", str[x]);
        if (str[x + 1] != NULL)
            return search_des(str, x + 1, usr);
        return SUCCESS;
    }
    if (is_empty(path) == 1)
        return not_empty(str, x, usr, path);
    remove(path);
    dprintf(1, "Type \033[1m\033[33m\" %s\"\033[0m successfully ", str[x]);
    dprintf(1, "\033[1m\033[31mdeleted\033[0m\n");
    if (str[x + 1] != NULL)
        return search_des(str, x + 1, usr);
    return SUCCESS;
}

int search_des(char **str, int x, struct usr_s *usr)
{
    if (str[x] == NULL)
        return SUCCESS;
    return destroy_dir(str, x, usr);
}

int remove_type(char **str, struct data_s **data, struct usr_s *usr)
{
    if (str[1] != NULL)
        return search_des(str, 1, usr);
    if (data == NULL)
        return SUCCESS;
    dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
    dprintf(1, " Missing arguments\n\n");
    return SUCCESS;
}