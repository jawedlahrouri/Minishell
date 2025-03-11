/*
** EPITECH PROJECT, 2025
** mini_shell1
** File description:
** mini_shell1
*/

#include "my.h"
#include "lib.h"

node_t *remove_element(node_t *list, char *element)
{
    node_t *current = list;
    node_t *temp = NULL;

    for (; current->env != NULL; current = current->next) {
        if (my_strncmp(element, current->next->env, my_strlen(element)) == 0) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return list;
        }
    }
    return list;
}
