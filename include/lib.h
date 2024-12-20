/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** printf
*/

#include <stdbool.h>
#include <unistd.h>

#ifndef LIB_H
    #define LIB_H
    #define ON 0
    #define OFF -1
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define ERROR_INT -1
    #define SUCCESS 0
    #define FAIL -1
    #define END -1

int my_strlen(char const *str);
int my_putstr(char const *str);
int my_dputstr(int file, char const *str);
int my_strcmp(const char *str1, const char *str2);
char *my_strcpy(char const *str);
int strstrlen(char **strstr);
char **add_list(char **list, char *add);
char *get_line(void);
bool is_a_word(char c);
char *my_realloc(char *str, size_t size);
char **cut(char *str);
void free_strstr(char **list);
int my_put_nbr(int nb);
int my_getnbr(char const *str);
int dir_exists(const char *path);
char *my_str_cmb(const char *str1, const char *str2);

#endif /* !LIB_H */
