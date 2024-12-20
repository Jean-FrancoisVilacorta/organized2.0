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
#include <unistd.h>

static int search_tag(char const *tag, char *path)
{
    char **tags = all_dir(path);

    for (int i = 0; tags[i] != NULL; i++) {
        if (my_strcmp(tags[i], tag) == 0)
            return i;
    }
    dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
    my_dputstr(2, " Tag '");
    my_dputstr(2, tag);
    my_dputstr(2, "' does not exits\n");
    dprintf(1, "\033[1m\033[33m[HACK]\033[0m Try to use the command ");
    dprintf(1, "\033[1m\033[38;5;214m\"type\"\033[0m\n\n");
    return ERROR_INT;
}

static void add_msg(struct data_s *new)
{
    my_putstr(new->tag);
    my_putstr(" n°");
    my_put_nbr(new->id);
    my_putstr(" - \"");
    my_putstr(new->name);
    my_putstr("\" \033[1m\033[32madded\033[0m\n");
}

static void add_to_data(struct data_s *new, struct usr_s *usr, char *path)
{
    char str[200];
    FILE *archivo = fopen(path, "a");

    sprintf(str, "%i;%s;%s;%s\n", usr->id, new->tag, new->name,new->path);
    fputs(str, archivo);
    fclose(archivo);
}

static int new_struct_2(struct data_s *new, struct usr_s *usr)
{
    char name_file[200];
    sprintf(name_file, "%s%s/%s", usr->path, new->tag, new->name);
    FILE *file = NULL;

    if (dir_exists(name_file) == 0)
        return -1;
    new->path = my_strdup(name_file);
    file = fopen(name_file, "w");
    fclose(file);
    sprintf(name_file, "%sdata.txt",  usr->path);
    add_to_data(new, usr, name_file);
    return SUCCESS;
}

static int new_struct(struct data_s *data, char *tag, char *name, struct usr_s *usr)
{
    struct data_s *new = malloc(sizeof(struct data_s) * 1);

    if (new == NULL) {
        free(tag);
        free(name);
        return ERROR_INT;
    }
    new->name = name;
    new->start = OFF;
    new->tag = tag;
    if (new_struct_2(new, usr) == -1) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, "\033[1m\033[32m%s\033[0m already exist in \033[1m\033[38;5;214m%s\033[0m\n", name, tag);
        free(name);
        free(tag);
        free(new);
        return SUCCESS;
    }
    new->id = usr->id;
    usr->id = usr->id + 1;
    new->next = NULL;
    new->before = data;
    data->next = new;
    new->end = ON;
    data->end = OFF;
    add_msg(new);
    return SUCCESS;
}

static int add_struct(struct data_s *data, char *tag, char *name, struct usr_s *usr)
{
    if (data->end != ON) {
        return add_struct(data->next, tag, name, usr);
    }
    if (data->name == NULL) {
        data->name = name;
        data->tag = tag;
        data->id = usr->id;
        usr->id = usr-> id + 1;
        add_msg(data);
        return SUCCESS;
    }
    return new_struct(data, tag, name, usr);
}

static int verify_add(char *tag, char *name, struct data_s *data,  struct usr_s *usr)
{
    int id_tag = search_tag(tag, usr->path);

    if (id_tag == ERROR_INT)
        return SUCCESS;
    return add_struct(data, my_strcpy(tag), my_strcpy(name), usr);
}

static int add_to(char **str, struct data_s *data, int x,  struct usr_s *usr)
{
    if (str[x + 1] == NULL)
        return EXIT_ERROR;
    if (verify_add(str[x], str[x + 1], data, usr) == ERROR_INT)
        return EXIT_ERROR;
    if (str[x + 2] == NULL)
        return SUCCESS;
    return add_to(str, data, x + 2, usr);
}

int add_data(char **str, struct data_s **data, struct usr_s *usr)
{
    return add_to(str, *data, 1, usr);
}

