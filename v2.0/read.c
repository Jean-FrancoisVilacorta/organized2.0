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

static char *desencrypt(char *file, struct usr_s *usr, int len)
{
    char exec[240 + len];
    char *dir = NULL;

    sprintf(exec, "./103cipher \"%s\" %s 1 > temp.txt", file, usr->password);
    system(exec);
    dir = open_file("temp.txt");
    system("rm temp.txt");
    return dir;
}

int nothing(char *path)
{
    FILE *archivo = fopen(path, "r");
    if (archivo == NULL) {
        return 1;
    }
    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    fclose(archivo);
    if (tamano == 0) {
        return 1;
    } else {
        return 0;
    }
}
int read_here(struct data_s *data, struct usr_s *usr)
{
    if (nothing(data->path) == 1) {
        dprintf(1, "Nothing no read\n\n");
        return SUCCESS;
    }
    char *file = open_file(data->path);
    int len = my_strlen(file);
    char *read = desencrypt(file, usr, len);

    dprintf(1, "\033[1m\033[38;5;214m[%s] %s:\033[0m\n", data->tag, data->name);
    dprintf(1, "%s\n", read);
    free(read);
    free(file);
    return SUCCESS;
}


static int search_the_id(int id, struct data_s *data, struct usr_s *usr)
{
    if (data->id == id)
        return read_here(data, usr);
    if (data->end == ON) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        my_putstr(" id \"");
        my_put_nbr(id);
        my_putstr("\" does not exist\n\n");
        return SUCCESS;
    }
    return search_the_id(id, data->next, usr);
}


int read_id(char **str, struct data_s **data, struct usr_s *usr)
{
    int len = strstrlen(str);
    int id = 0;

    if (len == 1) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, " Missing arguments\n\n");
        return SUCCESS;
    }
    id = atoi(str[1]);
    return search_the_id(id, *data, usr);
}