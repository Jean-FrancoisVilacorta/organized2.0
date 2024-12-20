##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Write a makefile for MiniShell1
##

SRC =	main.c		\
	organized.c		\
	src/add_data.c 	\
	src/del_data.c 	\
	src/disp_data.c 	\
	src/sort_data.c 	\
	src/order_by_alpha.c 	\
	src/order_by_type.c 	\
	src/order_by_nb.c 	\
	src/new_list_by_name.c 	\
	src/new_list_by_type.c 	\
	src/copy_all_names.c 	\
	src/copy_all_tag.c 	\
	src/reverse_list.c 	\
	lib/my_putstr.c 	\
	lib/my_dputstr.c 	\
	lib/my_strcmp.c 	\
	lib/my_strlen.c 	\
	lib/my_strcpy.c 	\
	lib/strstrlen.c 	\
	lib/get_line.c 		\
	lib/add_list.c 		\
	lib/is_a_word.c 	\
	lib/my_realloc.c 	\
	lib/my_strtok.c 	\
	lib/free_strstr.c 	\
	lib/my_put_nbr.c	\
	lib/my_getnbr.c		\
	lib/dir_exists.c		\
	lib/my_str_cmb.c		\
	v2.0/create_def_files.c		\
	v2.0/open_file.c		\
	v2.0/space_separator.c		\
	v2.0/log.c		\
	v2.0/extract_data.c		\
	v2.0/all_dir.c		\
	v2.0/type.c		\
	v2.0/help.c		\
	v2.0/remove.c		\
	v2.0/write.c		\
	v2.0/read.c		\
	

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g3

LDFLAGS = -L ./shell

LDLIBS = -lm -lmy

NAME = organized

MAKE = make

all:	$(NAME)

clib:
	$(MAKE) -C lib/my/

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -I ./include/ $(CFLAGS) $(LDFLAGS) -lshell

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
