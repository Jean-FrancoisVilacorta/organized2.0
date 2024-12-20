/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void del_msg(struct data_s *new)
{
    my_putstr(new->tag);
    my_putstr(" n°");
    dprintf(1, "\033[1m\033[31m%i\033[0m.", new->id);
    my_putstr(" - \"");
    dprintf(1, "\033[1m\033[32m%s\033[0m\"", new->name);
    dprintf(1, "\033[1m\033[31m deleted\033[0m.\n");
}

static bool is_number(char const *nb)
{
    for (int x = 0; nb[x] != '\0'; x++) {
        if (nb[x] < '0' || nb[x] > '9')
            return false;
    }
    return true;
}

int errease(const char *path, const char *linea_a_eliminar)
{
    FILE *archivo_original = fopen(path, "r");
    FILE *archivo_temp = tmpfile();
    char linea[1024];
    if (archivo_original == NULL)
        return 1;
    while (fgets(linea, sizeof(linea), archivo_original)) {
        if (strncmp(linea, linea_a_eliminar, strlen(linea_a_eliminar)) != 0)
            fputs(linea, archivo_temp);
    }
    fclose(archivo_original);
    archivo_original = fopen(path, "w");
    rewind(archivo_temp);
    while (fgets(linea, sizeof(linea), archivo_temp)) {
        fputs(linea, archivo_original);
    }
    fclose(archivo_original);
    fclose(archivo_temp);
    return 0;
}

static void remove_file(struct data_s *data, struct usr_s *usr)
{
    char line[200];
    char data_file[200];

    sprintf(line, "%i;%s;%s;%s", data->id, data->tag, data->name, data->path);
    sprintf(data_file, "%sdata.txt", usr->path);
    remove(data->path);
    errease(data_file, line);
}

static int start(struct data_s *data)
{
    struct data_s *next = data->next;

    free(data->name);
    free(data->tag);
    if (data->end == ON) {
        data->name = NULL;
        data->tag = NULL;
        return SUCCESS;
    }
    data->end = next->end;
    data->id = next->id;
    data->name = next->name;
    data->tag = next->tag;
    data->next = next->next;
    if (next->end == OFF)
        next->next->before = data;
    free(next);
    return SUCCESS;
}

static int deleted_normal(struct data_s *data)
{
    free(data->name);
    free(data->tag);
    free(data->path );
    if (data->end == ON) {
        data->before->end = ON;
    }
    data->before->next = data->next;
    free(data);
    return SUCCESS;
}

static int deleted(struct data_s *data, struct usr_s *usr)
{
    if (data->name == NULL) {
        return SUCCESS;
    }
    remove_file(data, usr);
    if (data->start == ON)
        return start(data);
    return deleted_normal(data);
}

static int del_by_id(int const nb, struct data_s *data, struct usr_s *usr)
{
    if (data->id == nb && data->name != NULL) {
        del_msg(data);
        return deleted(data, usr);
    }
    if (data->end == ON) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        my_putstr(" id \"");
        my_put_nbr(nb);
        my_putstr("\" does not exist\n\n");
        return SUCCESS;
    }
    return del_by_id(nb, data->next, usr);
}

static int verify_nb(char *str, struct data_s **data, struct usr_s *usr)
{
    int nb = 0;

    if (!is_number(str))
        return ERROR_INT;
    nb = my_getnbr(str);
    del_by_id(nb, *data, usr);
    return SUCCESS;
}

static int search_nb(char **str, struct data_s **data, int x, struct usr_s *usr)
{
    if (verify_nb(str[x], data, usr) == ERROR_INT)
        return SUCCESS;
    if (str[x + 1] == NULL)
        return SUCCESS;
    return search_nb(str, data, x + 1, usr);
}

int del_data(char **str, struct data_s **data, struct usr_s *usr)
{
    return search_nb(str, data, 1, usr);
}
