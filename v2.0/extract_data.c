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

static int default_struct(struct usr_s *usr, char *path)
{
    struct data_s *data = malloc(sizeof(struct data_s) * 1);
    FILE *file = fopen(path, "w");

    data->next = NULL;
    data->before = NULL;
    data->id = -1;
    data->tag = NULL;
    data->name = NULL;
    data->end = ON;
    data->start = ON;
    fclose(file);
    free(path);
    return run_organized(usr, data);
}

void free_usr(struct usr_s *usr)
{
    free(usr->password);
    free(usr->usr);
    free(usr->path);
    free(usr);
}

struct data_s *add_info(char **info)
{
    struct data_s *new = malloc(sizeof(struct data_s));

    new->id = atoi(info[ID]);
    new->tag = info[TYPE];
    new->name = info[NAME];
    new->path = info[PATH];
    new->next = NULL;
    new->before = NULL;
    new->start = OFF;
    new->end = OFF;
    free(info);
    return new;
}

struct data_s *add_file_data(char *str)
{
    char **info = NULL;

    if (str == NULL)
        return NULL;
    if (str[0] == '\0' || str[0] == '\n')
        return NULL;
    info =  cut(str);
    return add_info(info);
}

static void add_to_data(struct data_s *data, struct data_s *temp)
{
    if (data->end == ON) {
        temp->before = data;
        temp->end = ON;
        data->next = temp;
        data->end = OFF;
        return;
    }
    return add_to_data(data->next, temp);
}

static int open_data(struct usr_s *usr, char *path)
{
    FILE *file = fopen(path, "r");
    char line[100];
    struct data_s *data = NULL;
    struct data_s *temp = NULL;

    while (fgets(line, sizeof(line), file) != NULL) {
        temp = add_file_data(line);
        if (data == NULL && temp != NULL) {
            data = temp;
            data->end = ON;
            data->start = ON;
            if (temp->id >= usr->id)
                usr->id = temp->id + 1;
        }
        else if (temp != NULL) {
            add_to_data(data, temp);
            if (temp->id >= usr->id)
                usr->id = temp->id + 1;
        }
    }
    fclose(file);
    if (data == NULL)
        return default_struct(usr, path);
    free(path);
    return run_organized(usr, data);
}

static int extract_file_data(struct usr_s *usr)
{
    char *data_file = my_str_cmb(usr->path, "data.txt");

    if (dir_exists(data_file) == SUCCESS) {
        return open_data(usr, data_file);
    }
    
    return default_struct(usr, data_file);
}

int extract_data(char *path, char *usr, char *password)
{
    char *new_path = my_str_cmb(path, "/");
    struct usr_s *usr_data = malloc(sizeof(struct usr_s));

    usr_data->id = 0;
    usr_data->usr = usr;
    usr_data->password = password;
    usr_data->path = new_path;
    free(path);
    return extract_file_data(usr_data);
}