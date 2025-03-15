/*
** EPITECH PROJECT, 2025
** lib
** File description:
** free_array
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void free_array(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}
