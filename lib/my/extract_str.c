/*
** EPITECH PROJECT, 2025
** lib
** File description:
** extract_str
*/

#include <unistd.h>
#include <stdlib.h>

char *extract_str(char *str, char separator)
{
    char *start = NULL;
    size_t length;
    char *result = NULL;

    if (!str)
        return NULL;
    for (; *str && *str != separator; str++);
    if (!*str)
        return NULL;
    str++;
    start = str;
    for (; *str && *str != separator; str++);
    length = str - start;
    result = (char *)malloc(length + 1);
    if (!result)
        return NULL;
    for (size_t i = 0; i < length; i++)
        result[i] = start[i];
    result[length] = '\0';
    return result;
}
