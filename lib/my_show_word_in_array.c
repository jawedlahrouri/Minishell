/*
** EPITECH PROJECT, 2025
** lib
** File description:
** show word in array
*/

#include "lib.h"

void my_show_word_in_array(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        my_printf("%s\n", tab[i]);
}
