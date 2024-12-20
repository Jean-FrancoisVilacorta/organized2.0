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

char *get_def_file(void)
{
    const char *home = getenv("HOME");
    char *path_end = my_str_cmb(home, "/organized");

    return path_end;
}

int create_dir(char *path, int times)
{
    int result = mkdir(path, 0777);

    if (result != SUCCESS) {
        if (times == 5)
            return ERROR_INT;
        create_dir(path, times + 1);
    }
    return 0;
}

int yes_or_not(void)
{
    char *answer = get_line();

    if (my_strcmp(answer, "Y") == SUCCESS || my_strcmp(answer, "yes") == SUCCESS) {
        free(answer);
        return SUCCESS;
    }
    if (my_strcmp(answer, "N") == SUCCESS || my_strcmp(answer, "no") == SUCCESS) {
        free(answer);
        return FAIL;
    }
    free(answer);
    return yes_or_not();
}

static int make_usr_dir(char *path, char *usr, char *password, char *file)
{

    char *new_path = my_str_cmb(path, file);

    create_dir(new_path, 0);    
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
    return make_usr_dir(path, usr, password, secret_file);
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

int create_password(char *path, char *usr)
{
    char *password = NULL;

    dprintf(1, "\033[35m[%s]\033[0m", usr);
    my_putstr("-> ");
    password = get_line();
    dprintf(1, "Are you sure the password \"%s\" is correct? [N/Y]\n", password);

    dprintf(1, "\033[35m[%s]\033[0m", usr);
    my_putstr("-> ");
    if (yes_or_not() == FAIL) {
        free(password);
        return create_password(path, usr);
    }
    return create_dir_usr(path, usr, password);
}

int create_usr(char *path)
{
    char *usr = NULL;

    printf("Tell me, what do you want to call yourself?\n");
    dprintf(1, "\033[35m[~]\033[0m");
    my_putstr("-> ");
    usr = get_line();
    if (my_strlen(usr) > 12) {
        free(usr);
        printf("The username cannot be longer than \033[1;31m12 characters\033[0m\n");
        return create_usr(path);
    }
    printf("Now enter your password\n");
    return create_password(path, usr);
}

int create_def_files(void)
{
    char *path = get_def_file();
    system("clear");

    if (path == NULL)
        return ERROR_INT;
    printf("%s\n", path);
    if (create_dir(path, 0) == ERROR_INT) {
        free(path);
        my_dputstr(2, "dir can not be created\n");
        return ERROR_INT;
    }
    printf("Welcome to \033[1;33mOrganize v.2\033[0m. \n");
    printf("To get started you need to create your user account.\n\n");
    return create_usr(path);
}