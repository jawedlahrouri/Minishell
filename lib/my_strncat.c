/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** WIP
*/

#include "lib.h"

char *my_strncat(char *dest, const char *src, size_t n)
{
    char *pos = dest;

    while (*pos)
        pos++;
    while (*src && n > 0) {
        *pos = *src;
        pos++;
        src++;
        n--;
    }
    *pos = '\0';
    return dest;
}
