/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdlib.h>

static void swap(struct data_s *start, struct data_s *next)
{
    int id = start->id;
    char *tag = start->tag;
    char *name = start->name;

    start->id = next->id;
    start->tag = next->tag;
    start->name = next->name;
    next->id = id;
    next->tag = tag;
    next->name = name;
}

static void minor(struct data_s *start, struct data_s *next)
{
    if (my_strcmp(start->tag, next->tag) <= 0)
        swap(start, next);
    if (next->end == ON)
        return;
    minor(start, next->next);
}

static struct data_s *sort(struct data_s *start)
{
    if (start->end == ON)
        return start;
    minor(start, start->next);
    sort(start->next);
    return start;
}

void order_by_type_alpha(struct data_s **data)
{
    *data = sort(*data);
}
