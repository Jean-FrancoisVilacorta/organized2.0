/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** display one by one, the characters of a string
*/

int my_strlen(char const *str)
{
    int count = 0;

    while (str[count] != '\0')
        count++;
    return count;
}
