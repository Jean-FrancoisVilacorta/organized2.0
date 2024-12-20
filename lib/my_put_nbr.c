/*
** EPITECH PROJECT, 2024
** my_put_nbr.c
** File description:
** display the number given
*/

#include <unistd.h>
#include "../include/lib.h"

static int my_putchar(char c)
{
    return write(1, &c, 1);
}

static void time_to_print(int temp_nb)
{
    if (temp_nb >= 10) {
        time_to_print(temp_nb / 10);
    }
    if (temp_nb % 10 + '0' == '(') {
        my_put_nbr(21474);
        my_put_nbr(83648);
        return;
    }
    my_putchar(temp_nb % 10 + '0');
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        nb = nb * (-1);
        my_putchar('-');
    }
    time_to_print(nb);
    return 0;
}
