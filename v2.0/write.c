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

static char *encrypt(char *file, struct usr_s *usr, int len)
{
    char exec[240 + len];
    char *dir = NULL;

    sprintf(exec, "./103cipher \"%s\" %s 0 > temp.txt", file, usr->password);
    system(exec);
    dir = open_file("temp.txt");
    system("rm temp.txt");
    return dir;
}

int write_secret(char *path, char *str)
{
    FILE *archivo = fopen(path, "w");

    if (archivo == NULL)
        return -1;
    if (fputs(str, archivo) == EOF) {
        return -1;
    }
    fclose(archivo);
    dprintf(1, "\033[1m\033[32mWrite successfully\033[0m\n");
    return 0;
}

int write_here(char *str, struct data_s *data, struct usr_s *usr)
{
    int len = my_strlen(str);
    char *secret = encrypt(str, usr, len);

    write_secret(data->path, secret);
    free(secret);
    return SUCCESS;
}

static int search_the_id(int id, char *str, struct data_s *data, struct usr_s *usr)
{
    if (data->id == id)
        return write_here(str, data, usr);
    if (data->end == ON) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        my_putstr(" id \"");
        my_put_nbr(id);
        my_putstr("\" does not exist\n\n");
        return SUCCESS;
    }
    return search_the_id(id, str, data->next, usr);
}

static char *obtain_msg(char **str, int x, char *ret)
{
    char *new = NULL;
    char *space = NULL;

    if (str[x] == NULL)
        return ret;
    if (ret == NULL) {
        new = my_strdup(str[x]);
        return obtain_msg(str, x + 1, new);
    }
    space = my_str_cmb(ret, " ");
    free(ret);
    new = my_str_cmb(space, str[x]);
    return obtain_msg(str, x + 1, new);
}

int write_id(char **str, struct data_s **data, struct usr_s *usr)
{
    int len = strstrlen(str);
    int id = 0;
    char *msg = NULL;

    if (len < 3) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, " Missing arguments\n\n");
        return SUCCESS;
    }
    id = atoi(str[1]);
    msg = obtain_msg(str, 2, NULL);
    return search_the_id(id, msg, *data, usr);
}