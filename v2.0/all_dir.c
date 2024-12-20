/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char *my_strdup(char *str)
{
    char *new = NULL;
    int len = 0;

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    new = malloc(sizeof(char) * (len + 1));
    for (int i = 0; str[i] != '\0'; i++)
        new[i] = str[i];
    new[len] = '\0';
    return new;
}

static char **finish(char **list, char *add, int len)
{
    char **new = malloc(sizeof(char *) * (len + 2));
    int x = 0;

    while (list[x] != NULL) {
        new[x] = list[x];
        x++;
    }
    new[x] = my_strdup(add);
    new[x + 1] = '\0';
    free(list);
    return new;
}

char **add_to_list(char **list, char *add)
{
    int len = strstrlen(list);
    char **new = NULL;

    if (len == 0) {
        new = malloc(sizeof(char *) * 2);
        new[0] = my_strdup(add);
        new[1] = NULL;
        return new;
    }
    return finish(list, add, len);
}

char **all_dir(const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat st;
    char **all = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char ruta_completa[1024];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", path, entry->d_name);
        if (stat(ruta_completa, &st) == 0 && S_ISDIR(st.st_mode)) {
            all = add_list(all, entry->d_name);
        }
    }
    closedir(dir);
    return all;
}