/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static bool its_a_word(char c, char *flag)
{
    int x = 0;

    if (c == '\0')
        return false;
    while (flag[x] != '\0') {
        if (flag[x] == c)
            return false;
        x++;
    }
    return true;
}

static int how_many_cut(char *str)
{
    int space = OFF;
    int x = 0;
    int count = 0;

    while (str[x] != '\0') {
        if (its_a_word(str[x], ";, \t\n") && space == OFF) {
            count++;
            space = ON;
        }
        if (!its_a_word(str[x], ";, \t\n")) {
            space = OFF;
        }
        x++;
    }
    return count;
}

static int count(char *str, int x)
{
    int i = 0;

    while (str[x] != '\0') {
        if (!its_a_word(str[x], ";, \t\n"))
            return i;
        i++;
        x++;
    }
    return i;
}

static char *extract_str(char *str, int x)
{
    int len = count(str, x);
    char *new = malloc(sizeof(char) * (len + 1));
    int i = 0;

    while (its_a_word(str[x], ";, \t\n")) {
        new[i] = str[x];
        i++;
        x++;
    }
    new[len] = '\0';
    return new;
}

static int next(char *str, int x)
{
    while (its_a_word(str[x], ";, \t\n")) {
        x++;
    }
    return x;
}

static char **make_lib(char *str, int size)
{
    char **lib = malloc(sizeof(char *) * (size + 1));
    int x = 0;
    int i = 0;

    while (str[x] != '\0' && i != size) {
        if (its_a_word(str[x], ";, \t\n")) {
            lib[i] = extract_str(str, x);
            x = next(str, x);
            i++;
        } else {
            x++;
        }
    }
    lib[size] = NULL;
    return lib;
}

char **cut(char *str)
{
    int size = 0;

    if (str == NULL)
        return NULL;
    size = how_many_cut(str);
    if (size == 0)
        return NULL;
    return make_lib(str, size);
}
