/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** printf
*/

#include <stddef.h>

#ifndef MY_H
    #define MY_H
    #define ON 0
    #define OFF -1
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define ERROR_INT -1
    #define SUCCESS 0
    #define FAIL -1
    #define END -1
    #define EXIT 2
    #define MAX_CHAR 6000
    #define ID 0
    #define TYPE 1
    #define NAME 2
    #define PATH 3

struct data_s {
    struct data_s *next;
    struct data_s *before;
    int id;
    char *tag;
    char *name;
    char *path;
    int end;
    int start;
};

struct usr_s {
    char *usr;
    char *password;
    char *path;
    int id;
};

struct flag_long_s {
    char *flag;
    int (*func)(char **, struct data_s **, struct usr_s *);
};

void help_type(void);
void help_remove(void);
void help_write(void);
void help_read(void);
void help_sort(void);
void help_disp(void);

struct help_s {
    char *flag;
    void (*func)(void);
};

static const struct help_s help_flag[] = {
    {"type", help_type},
    {"remove", help_remove},
    {"write", help_write},
    {"read", help_read},
    {"sort", help_sort},
    {"disp", help_disp},
    {NULL, NULL},
};

int add_data(char **str, struct data_s **data, struct usr_s *usr);
int del_data(char **str, struct data_s **data, struct usr_s *usr);
int disp_data(char **str, struct data_s **data, struct usr_s *usr);
int remove_type(char **str, struct data_s **data, struct usr_s *usr);
int type(char **str, struct data_s **data, struct usr_s *usr);
int help(char **str, struct data_s **data, struct usr_s *usr);
int write_id(char **str, struct data_s **data, struct usr_s *usr);
int read_id(char **str, struct data_s **data, struct usr_s *usr);
int sort_datax(char **str, struct data_s **data, struct usr_s *usr);

static const struct flag_long_s flag_long[] = {
    {"add", add_data},
    {"del", del_data},
    {"disp", disp_data},
    {"sort", sort_datax},
    {"type", type},
    {"help", help},
    {"remove", remove_type},
    {"write", write_id},
    {"read", read_id},
    {NULL, NULL},
};

int organized(int const ac, char const **av);
void free_list(struct data_s *to_order);
int run_organized(struct usr_s *usr, struct data_s *data);
void order_by_alpha(struct data_s **data);
void order_by_nb(struct data_s **data);
void order_by_type_alpha(struct data_s **data);
char **copy_all_names(struct data_s *list);
struct data_s *all_data_named_like(struct data_s *to_order, char *name);
struct data_s *all_data_type_like(struct data_s *to_order, char *name);
struct data_s *reverse_list(struct data_s *list, struct data_s *new);
char **copy_all_tag(struct data_s *list);
int order_this(char **str, struct data_s **to_order,
    int x);
int print_table(struct data_s *data);
int create_def_files(void);
char *open_file(char const *filepath);
char **my_spaces(char const *str);

char *get_def_file(void);
int create_usr(char *path);
int loggin(char *path);
int extract_data(char *path, char *usr, char *password);
void free_usr(struct usr_s *usr);
char **all_dir(const char *path);
char *my_strdup(char *str);
int create_dir(char *path, int times);
int add_type(char **str, int x, struct usr_s *usr);
int yes_or_not(void);
int search_des(char **str, int x, struct usr_s *usr);

#endif /* !MY_H */
