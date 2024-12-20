/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** get the number of a string
*/

static int extra_special_case(char const *str, int x)
{
    if (str[x + 9] != '8')
        return -1;
    if (x == 0)
        return -1;
    if (str[x - 1] == '-')
        return -2147483648;
    return -1;
}

static int part_2_sp_c(char const *str, int x)
{
    if (str[x + 6] > '3')
        return -1;
    if (str[x + 7] > '6')
        return -1;
    if (str[x + 8] > '4')
        return -1;
    if (str[x + 9] > '7') {
        return extra_special_case(str, x);
    }
    return 0;
}

static int special_case(char const *str, int x)
{
    if (str[x] > '2')
        return -1;
    if (str[x + 1] > '1')
        return -1;
    if (str[x + 2] > '4')
        return -1;
    if (str[x + 3] > '7')
        return -1;
    if (str[x + 4] > '4')
        return -1;
    if (str[x + 5] > '8')
        return -1;
    return part_2_sp_c(str, x);
}

static int verify_size(char const *str, int x)
{
    int count = 0;
    int a = x;

    while (str[x] >= '0' && str[x] <= '9') {
        x++;
        count++;
    }
    if (count < 10)
        return 0;
    if (count > 10)
        return -1;
    return special_case(str, a);
}

static int verify_negative(char const *str, int x, int neg)
{
    if (x == -1)
        return neg;
    if (str[x] != '+' && str[x] != '-')
        return neg;
    if (str[x] == '-')
        neg = neg * -1;
    return verify_negative(str, x - 1, neg);
}

static int verify_number(char const *str, int x)
{
    int negative = 0;
    int res = 0;

    negative = verify_negative(str, x - 1, 1);
    if (verify_size(str, x) == -1)
        return 0;
    while (str[x] >= '0' && str[x] <= '9') {
        res = res * 10 + str[x] - '0';
        x++;
    }
    if (negative == -1)
        res = res * -1;
    return res;
}

static int error_case(char const *str)
{
    int x = 0;

    if (str[0] == '\0')
        return 0;
    while (str[x] != '\0') {
        if (str[x] >= '0' && str[x] <= '9')
            return verify_number(str, x);
        x++;
    }
    return 0;
}

int my_getnbr(char const *str)
{
    return error_case(str);
}
