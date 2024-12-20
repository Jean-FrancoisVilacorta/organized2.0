/*
** EPITECH PROJECT, 2024
** setting_open.c
** File description:
** open a file
*/

#include "../include/lib.h"
#include <stdlib.h>

static int search_error(char const *str)
{
    if (str == NULL)
        return FAIL;
    if (str[0] == '\0')
        return FAIL;
    return SUCCESS;
}

static int count_lines(char const *str)
{
    int line = 1;

    for (int x = 0; str[x] != '\0'; x++) {
        if (str[x] == ' ')
            line = line + 1;
        if (str[x] == ' ' && str[x + 1] == '\0')
            line--;
    }
    return line;
}

static char *extract_str(char const *str, int *x, int len)
{
    int i = *x;
    int a = 0;
    char *add = malloc(sizeof(char) * (len + 1));

    while (str[i] != ' ' && str[i] != '\0') {
        add[a] = str[i];
        i++;
        a++;
    }
    add[len] = '\0';
    *x = i;
    return add;
}

static char *search_line(char const *str, int *x)
{
    int len = *x;

    while (str[len] == ' ' || str[len] == '\0') {
        if (str[len] == '\0') {
            *x = END;
            return NULL;
        }
        *x = len + 1;
        return search_line(str, x);
    }
    while (str[len] != ' ' && str[len] != '\0')
        len++;
    return extract_str(str, x, len - *x);
}

static char **add_lines(char const *str, char **ret, int lines)
{
    int x = 0;

    for (int i = 0; i != lines; i++) {
        ret[i] = search_line(str, &x);
        if (x == END) {
            return ret;
        }
    }
    return ret;
}

static char **start(char const *str)
{
    int line = count_lines(str);
    char **ret = malloc(sizeof(char *) * (line + 1));

    for (int i = 0; i != line + 1; i++)
        ret[i] = NULL;
    return add_lines(str, ret, line);
}

char **my_spaces(char const *str)
{
    if (search_error(str))
        return NULL;
    return start(str);
}
