/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdlib.h>

static struct data_s *copy(struct data_s *to_order)
{
    struct data_s *copy = malloc(sizeof(struct data_s));

    copy->name = NULL;
    copy->next = NULL;
    copy->before = NULL;
    copy->start = ON;
    copy->end = OFF;
    copy->id = to_order->id;
    copy->name = to_order->name;
    copy->tag = to_order->tag;
    return copy;
}

static struct data_s *add_to_list(struct data_s *to_order,
    struct data_s *new)
{
    struct data_s *add = NULL;

    if (new->name == NULL) {
        new->id = to_order->id;
        new->name = to_order->name;
        new->tag = to_order->tag;
        return new;
    }
    add = copy(to_order);
    new->start = OFF;
    add->next = new;
    return add;
}

static struct data_s *search_name(struct data_s *to_order, char *name,
    struct data_s *new)
{
    if (my_strcmp(name, to_order->name) == 0)
        new = add_to_list(to_order, new);
    if (to_order->end == ON)
        return new;
    return search_name(to_order->next, name, new);
}

struct data_s *all_data_named_like(struct data_s *to_order, char *name)
{
    struct data_s *new = malloc(sizeof(struct data_s));

    new->name = NULL;
    new->next = NULL;
    new->before = NULL;
    new->start = ON;
    new->end = ON;
    return search_name(to_order, name, new);
}
