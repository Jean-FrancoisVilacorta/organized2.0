/*
** EPITECH PROJECT, 2024
** organized.c
** File description:
** organise data
*/

#include "../include/my.h"
#include "../include/lib.h"
#include "../shell/shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int verification(char *path, char *usr, char *password, char *file)
{
    char *new_path = my_str_cmb(path, file);

    if (dir_exists(new_path) == FAIL) {
        free(new_path);
        free(usr);
        free(password);
        dprintf(1, "\n\033[1m\033[31m[ERROR]\033[0m \033[1m\033[31mBad Loggin\033[0m\n");
        dprintf(1, "-the \033[34mpassword\033[0m or \033[32muser\033[0m are wrong\n");
        return loggin(path);
    }
    dprintf(1, "\033[1m\033[32mSuccessful logging\033[0m\n\n");
    dprintf(1, "Welcome back \033[35m%s\033[0m\n", usr);
    free(path);
    return extract_data(new_path, usr, password);
}

static int dir_usr(char *path, char *usr, char *password, char **key)
{
    char secret_file[15];
    int temp = 0;

    for (int i = 1; i != 12 && key[i] != NULL; i++) {
        for (int x = 0; key[i][x] != '\0'; x++) {
            temp = temp + key[i][x];
            if (temp > 126)
                break;
            secret_file[i] = temp;
            secret_file[i + 1] = '\0';
        }
        temp = 0;
    }
    secret_file[0] = '/';
    free_strstr(key);
    return verification(path, usr, password, secret_file);
}

static int create_dir_usr(char *path, char *usr, char *password)
{
    char exec[240];
    char *dir = NULL;
    char **key = NULL;

    sprintf(exec, "./103cipher \"%s\" %s 0 > temp.txt", usr, password);
    system(exec);
    dir = open_file("temp.txt");
    system("rm temp.txt");
    key = my_spaces(dir);
    free(dir);
    return dir_usr(path, usr, password, key);
}

int password(char *path, char *usr)
{
    char *password = NULL;

    dprintf(1, "\033[1m\033[34mpassword:\033[0m \n");
    dprintf(1, "\033[35m[~]\033[0m");
    my_putstr("-> ");
    password = get_line();
    return create_dir_usr(path, usr, password);
}

int loggin(char *path)
{
    char *usr = NULL;

    dprintf(1, "\n\033[1m\033[32musername:\033[0m \n");
    dprintf(1, "\033[35m[~]\033[0m");
    my_putstr("-> ");
    usr = get_line();
    if (my_strlen(usr) > 12) {
        free(usr);
        printf("The username cannot be longer than \033[1;31m12 characters\033[0m\n");
        return loggin(path);
    }
    return password(path, usr);
}