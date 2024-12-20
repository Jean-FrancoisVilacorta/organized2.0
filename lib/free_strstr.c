/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdlib.h>
#include "../include/my.h"

void free_list(struct data_s *to_order)
{
    if (to_order->end != ON) {
        free_list(to_order->next);
    }
    free(to_order);
}

void free_strstr(char **list)
{
    for (int i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}
