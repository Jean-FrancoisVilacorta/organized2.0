/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdio.h>

int print_table(struct data_s *data)
{
    if (data->end == OFF)
        print_table(data->next);
    my_putstr(data->tag);
    my_putstr(" n°");
    my_put_nbr(data->id);
    my_putstr(" - \"");
    my_putstr(data->name);
    my_putstr("\"\n");
    return 0;
}

static int print_table_by_name(struct data_s *data, char *name)
{
    if (data->end == OFF)
        print_table_by_name(data->next, name);
    if (my_strcmp(name, data->name) != 0)
        return 0;
    my_putstr(data->tag);
    my_putstr(" n°");
    my_put_nbr(data->id);
    my_putstr(" - \"");
    dprintf(1, "\033[32m%s\033[0m", data->name);
    my_putstr("\"\n");
    return 0;
}

static int print_table_by_type(struct data_s *data, char *type)
{
    if (data->end == OFF)
        print_table_by_type(data->next, type);
    if (my_strcmp(type, data->tag) != 0)
        return 0;
    dprintf(1, "\033[38;5;214m%s\033[0m", data->tag);
    my_putstr(" n°");
    my_put_nbr(data->id);
    my_putstr(" - \"");
    my_putstr(data->name);
    my_putstr("\"\n");
    return 0;
}


int disp_data(char **str, struct data_s **data, struct usr_s *usr)
{
    int len = strstrlen(str);

    if ((*data)->name == NULL) {
        my_putstr("Nothing to display\n");
        return EXIT_ERROR;
    }
    if (len == 3) {
        if (my_strcmp("-n", str[1]) == 0)
            return print_table_by_name(*data, str[2]);
        if (my_strcmp("-t", str[1]) == 0)
            return print_table_by_type(*data, str[2]);
    }
    print_table(*data);
    if (usr == NULL)
        return 0;
    return SUCCESS;
}
