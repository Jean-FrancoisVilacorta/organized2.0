/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdlib.h>
#include "../include/lib.h"

char **add_list(char **list, char *add)
{
    char **ret = NULL;
    int len = 0;

    if (list == NULL) {
        ret = malloc(sizeof(char *) * 2);
        ret[0] = add;
        ret[1] = NULL;
        return ret;
    }
    len = strstrlen(list);
    ret = malloc(sizeof(char *) * (len + 2));
    for (int i = 0; list[i] != NULL; i++)
        ret[i] = list[i];
    ret[len] = add;
    ret[len + 1] = NULL;
    free(list);
    return ret;
}
