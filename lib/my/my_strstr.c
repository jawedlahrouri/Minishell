/*
** EPITECH PROJECT, 2025
** lib
** File description:
** strstr
*/

#include "lib.h"

char *my_strstr(char *haystack, char *needle)
{
    char *h = NULL;
    char *n = NULL;

    if (!*needle)
        return haystack;
    while (*haystack) {
        h = haystack;
        n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n)
            return haystack;
        haystack++;
    }
    return NULL;
}