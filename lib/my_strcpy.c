/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdio.h>
#include <stdlib.h>

static int count(char const *str)
{
    int len = 0;

    if (str == NULL)
        return -1;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *my_strcpy(char const *str)
{
    int len = count(str);
    char *ret = NULL;

    if (len == -1)
        return NULL;
    ret = malloc(sizeof(char) * (len + 2));
    for (int i = 0; str[i] != '\0'; i++) {
        ret[i] = str[i];
    }
    ret[len] = '\0';
    ret[len + 1] = '\0';
    return ret;
}
