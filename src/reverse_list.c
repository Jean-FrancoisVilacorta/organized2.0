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

static struct data_s *copy_list(struct data_s *list)
{
    struct data_s *copy = malloc(sizeof(struct data_s));

    copy->end = list->end;
    copy->start = list->start;
    copy->name = list->name;
    copy->tag = list->tag;
    copy->id = list->id;
    return copy;
}

static void end_or_start_case(struct data_s *list, struct data_s *copy)
{
    if (list->end == ON) {
        copy->start = ON;
        copy->end = OFF;
    }
    if (list->start == ON) {
        copy->end = ON;
        copy->start = OFF;
    }
}

struct data_s *reverse_list(struct data_s *list, struct data_s *new)
{
    struct data_s *copy = NULL;

    if (list->end == ON && list->start == ON)
        return list;
    copy = copy_list(list);
    end_or_start_case(list, copy);
    copy->next = new;
    if (new != NULL)
        new->before = copy;
    if (copy->start == ON)
        return copy;
    return reverse_list(list->next, copy);
}
