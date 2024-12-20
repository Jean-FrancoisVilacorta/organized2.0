/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include <stdbool.h>

bool is_a_word(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
