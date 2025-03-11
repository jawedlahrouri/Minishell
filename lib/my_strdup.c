/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** write string
*/

#include <stdlib.h>
#include "lib.h"

char *my_strdup(char const *src)
{
    int srclen = my_strlen(src);
    char *dest = malloc(sizeof(char) * (srclen + 1));
    int i = 0;

    if (dest == NULL)
        return NULL;
    for (; srclen != i; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
