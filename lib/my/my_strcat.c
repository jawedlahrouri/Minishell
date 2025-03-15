/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** a function that concatenates two strings
*/

#include <stdio.h>

char *my_strcat(char *dest, const char *src)
{
    char *pos = dest;

    while (*pos)
        pos++;
    while (*src) {
        *pos = *src;
        pos++;
        src++;
    }
    *pos = '\0';
    return dest;
}
