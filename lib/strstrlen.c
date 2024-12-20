/*
** EPITECH PROJECT, 2024
** setting_up
** File description:
** setting_up
*/

#include <stdlib.h>

int strstrlen(char **strstr)
{
    int x = 0;

    if (strstr == NULL)
        return 0;
    while (strstr[x] != NULL) {
        x++;
    }
    return x;
}
