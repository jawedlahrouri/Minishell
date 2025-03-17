/*
** EPITECH PROJECT, 2025
** lib
** File description:
** isdigit
*/

int my_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return 0;
    else
        return 1;
}
