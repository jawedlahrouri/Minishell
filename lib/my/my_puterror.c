/*
** EPITECH PROJECT, 2025
** lib
** File description:
** puterror
*/

#include "lib.h"
#include <unistd.h>

void my_puterror(char const *str)
{
    write(2, str, my_strlen(str));
}
