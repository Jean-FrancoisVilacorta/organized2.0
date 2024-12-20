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

void help_type(void)
{
    dprintf(1, "\033[1m\033[33mtype (\033[33m...\033[0m)\n");
    dprintf(1, "It is used to create a new type to categorize the infosignature.\n");
    dprintf(1, "Just type the command and then all the new categories you want to create.\n\n");
}

void help_remove(void)
{
    dprintf(1, "\033[1m\033[34mremove \033[0m(\033[1m\033[38;5;214m\"type\"\033[0m, \033[1m\033[38;5;214m...\033[0m)\n");
    dprintf(1, "Add the types you want to delete.\n");
    dprintf(1, "[Important] if you have files inside you can still delete them but it is not recommended.\n\n");
}

void help_write(void)
{
    dprintf(1, "\033[1m\033[32mwrite \033[0m(\033[38;5;214m\"id\"\033[0m (\033[38;5;214mmessage\033[0m))\n");
    dprintf(1, "To write a secret message to the file of the selected id.\n");
    dprintf(1, "Just type the id number and then the text you want to add. No need to add () or “”\n\n");
}

void help_read(void)
{
    dprintf(1, "\033[34mread \033[0m(\033[32m\"id\"\033[0m)\n");
    dprintf(1, "To read the secret message of an id.\n");
    dprintf(1, "in case the file is empty, a message will be displayed indicating that the file is empty.\n\n");
}

void help_sort(void)
{
    dprintf(1, "\033[34msort \033[0m(\033[0m\"ID | TYPE | NAME ... -r\"\033[0m)\n");
    dprintf(1, "To sort the printout. You can use more than one flag at a time.\n\n");
}

void help_disp(void)
{
    dprintf(1, "\033[1m\033[33mdisp \033[0m(\"_\" | ");
    dprintf(1, "\033[32m\"-n NAME\" \033[0m");
    dprintf(1, "\033[38;5;214m\"-t TYPE\"\033[0m)\n");
    dprintf(1, "To print all the information.\n");
    dprintf(1, "Also if you add -n, only the name you add afterwards will be printed.\n");
    dprintf(1, "And if -t is added, only the selected type will be printed.\n\n");
}

static int more_help(char *flag)
{
    int x = 0;

    while (help_flag[x].flag != NULL) {
        if (my_strcmp(help_flag[x].flag, flag) == 0) {
            help_flag[x].func();
            return 0;
        }
        x++;
    }
    return SUCCESS;
}

static void def_help(void)
{
    dprintf(1, "\033[1m\033[32m[add]\033[0m to add information for a specific tag\n");
    dprintf(1, "\033[1m\033[31m[del]\033[0m to delete an information from a specific tag\n");
    dprintf(1, "\033[1m\033[33m[disp]\033[0m to print all or certain data\n");
    dprintf(1, "\033[1m\033[34m[sort]\033[0m to arrange the data in a certain order\n");
    dprintf(1, "\033[1m\033[38;5;214m[type]\033[0m to add one or more types at a time\n");
    dprintf(1, "\033[1m\033[36m[remove]\033[0m to remove one or more types at a time\n");
    dprintf(1, "\033[1m\033[32m[write]\033[0m to write an encrypted message to an id\n");
    dprintf(1, "\033[1m\033[34m[read]\033[0m to read the encrypted message of an id\n");
    dprintf(1, "[help] for a guide on how to use each command by adding the command after help\n\n");
}

int help(char **str, struct data_s **data, struct usr_s *usr)
{
    if (str[1] != NULL)
        return more_help(str[1]);
    def_help();
    if (data == NULL)
        return SUCCESS;
    if (usr == NULL)
        return SUCCESS;
    return SUCCESS;
}