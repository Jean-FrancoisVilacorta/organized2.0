/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdlib.h>

static int my_pointlen(char **list)
{
    int x = 0;

    while (list[x] != NULL)
        x++;
    return x;
}

static char **new_name(char **list, char *str)
{
    int len = my_pointlen(list);
    char **new = malloc(sizeof(char *) * (len + 2));

    for (int i = 0; list[i] != NULL; i++) {
        new[i] = list[i];
    }
    new[len] = str;
    new[len + 1] = NULL;
    free(list);
    return new;
}

static char **next_name(char **names,
    struct data_s *list)
{
    int similarity = 0;

    for (int i = 0; names[i] != NULL; i++) {
        similarity = my_strcmp(names[i], list->tag);
        if (similarity == 0 && list->end == ON)
            return names;
        if (similarity == 0)
            return next_name(names, list->next);
    }
    names = new_name(names, list->tag);
    if (list->end == ON)
        return names;
    return next_name(names, list->next);
}

char **copy_all_tag(struct data_s *list)
{
    char **new_list = malloc(sizeof(char *) * 2);

    new_list[0] = list->tag;
    new_list[1] = NULL;
    return next_name(new_list, list);
}
