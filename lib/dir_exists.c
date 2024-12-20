/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main for the setting_up
*/

#include "../include/lib.h"
#include <sys/stat.h>

int dir_exists(const char *path)
{
    struct stat buffer;

    if (stat(path, &buffer) == 0)
        return SUCCESS;
    return FAIL;
}
