/*
** EPITECH PROJECT, 2025
** lib
** File description:
** isalpha
*/

int my_isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
        '_' == c || '.' == c)
        return 0;
    else
        return 1;
}
