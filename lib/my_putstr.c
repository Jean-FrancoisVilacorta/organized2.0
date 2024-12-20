/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display one by one, the characters of a string
*/

#include <unistd.h>
#include "../include/lib.h"

int my_putstr(char const *str)
{
    int count = my_strlen(str);
    int ret = 0;

    ret = write(1, str, count);
    return ret;
}

int my_putnstr(char const *str, int n)
{
    int count = my_strlen(str);
    int ret = 0;

    if (count > n)
        count = n;
    ret = write(1, str, count);
    return ret;
}
