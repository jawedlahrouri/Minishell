/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** send back the len of the input string which is nice
*/

#include "lib.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}
