/*
** EPITECH PROJECT, 2025
** lib
** File description:
** isalpha
*/

int my_isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 0;
    else
        return 84;
}
