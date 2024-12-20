/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display one by one, the characters of a string
*/

#include <unistd.h>
#include "../include/lib.h"

int my_dputstr(int file, char const *str)
{
    int count = my_strlen(str);
    int ret = 0;

    ret = write(file, str, count);
    return ret;
}
