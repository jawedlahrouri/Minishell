/*
** EPITECH PROJECT, 2025
** lib
** File description:
** free word array
*/

#include "lib.h"

void my_free_word_array(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}
