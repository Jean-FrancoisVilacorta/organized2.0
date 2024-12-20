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

static struct data_s *add_at_the_end(struct data_s *temp,
    struct data_s *final, int a)
{
    if (a == 0)
        return temp;
    if (final->end == ON) {
        final->end = OFF;
        final->next = temp;
        return final;
    }
    return add_at_the_end(temp, final->next, a);
}

static int new_order(struct data_s **to_order,
    char **str, int x)
{
    char **names = copy_all_names(*to_order);
    struct data_s *temp;
    struct data_s *final;
    int a = 0;

    for (int i = 0; names[i] != NULL; i++) {
        temp = all_data_named_like(*to_order, names[i]);
        if (temp->end == OFF)
            order_this(str, &temp, x);
        if (a == 0)
            final = add_at_the_end(temp, final, a);
        else
            add_at_the_end(temp, final, a);
        a = 1;
    }
    free(names);
    free_list(*to_order);
    *to_order = final;
    return SUCCESS;
}

static int new_type_order(struct data_s **to_order,
    char **str, int x)
{
    char **names = copy_all_tag(*to_order);
    struct data_s *temp;
    struct data_s *final;
    int a = 0;

    for (int i = 0; names[i] != NULL; i++) {
        temp = all_data_type_like(*to_order, names[i]);
        if (temp->end == OFF)
            order_this(str, &temp, x);
        if (a == 0)
            final = add_at_the_end(temp, final, a);
        else
            add_at_the_end(temp, final, a);
        a = 1;
    }
    free(names);
    free_list(*to_order);
    *to_order = final;
    return SUCCESS;
}

static int order_by_name(struct data_s **to_order,
    char **str, int x)
{
    order_by_alpha(to_order);
    if (str[x + 1] != NULL) {
        if (my_strcmp("-r", str[x + 1]) == 0) {
            x = x + 1;
            *to_order = reverse_list(*to_order, NULL);
        }
    }
    if (str[x + 1] == NULL)
        return SUCCESS;
    return new_order(to_order, str, x + 1);
}

static int order_by_type(struct data_s **to_order,
    char **str, int x)
{
    order_by_type_alpha(to_order);
    if (str[x + 1] != NULL) {
        if (my_strcmp("-r", str[x + 1]) == 0) {
            x = x + 1;
            *to_order = reverse_list(*to_order, NULL);
        }
    }
    if (str[x + 1] == NULL)
        return SUCCESS;
    return new_type_order(to_order, str, x + 1);
}

static int order_by_id(struct data_s **to_order,
    char **str, int x)
{
    order_by_nb(to_order);
    if (str[x + 1] != NULL) {
        if (my_strcmp("-r", str[x + 1]) == 0) {
            x = x + 1;
            *to_order = reverse_list(*to_order, NULL);
        }
    }
    if (str[x + 1] == NULL)
        return SUCCESS;
    return 0;
}

int order_this(char **str, struct data_s **to_order,
    int x)
{
    if (my_strcmp("NAME", str[x]) == 0)
        return order_by_name(to_order, str, x);
    if (my_strcmp("ID", str[x]) == 0)
        return order_by_id(to_order, str, x);
    if (my_strcmp("TYPE", str[x]) == 0)
        return order_by_type(to_order, str, x);
    return SUCCESS;
}

struct data_s *sort_data(char **str, struct data_s **data)
{
    order_this(str, data, 1);
    return *data;
}

static bool verify_type(char **argv, int x, char types[4][5])
{
    if (argv[x] == NULL)
        return true;
    for (int i = 0; i != 4; i++) {
        if (my_strcmp(argv[x], types[i]) == 0)
            return verify_type(argv, x + 1, types);
    }
    my_dputstr(2, "The type of sort that you select doesn't exist\n");
    return false;
}

int sort_datax(char **str, struct data_s **data, struct usr_s *usr)
{
    char types[4][5] = {"NAME", "ID", "TYPE", "-r"};

    if (str[1] == NULL) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, " Missing arguments\n\n");
        return 0;
    }
    if (!verify_type(str, 1, types)) {
        dprintf(1, "\033[1m\033[31m[UPS]\033[0m");
        dprintf(1, " wrong flag\n\n");
        return 84;
    }
    *data = sort_data(str, data);
    if (usr == NULL)
        return 0;
    return 0;
}
