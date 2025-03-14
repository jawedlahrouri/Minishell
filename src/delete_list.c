/*
** EPITECH PROJECT, 2025
** mini_shell1
** File description:
** mini_shell1
*/

#include "my.h"
#include "lib.h"

node_t *remove_first_element(node_t *list, char *element)
{
    node_t *temp;

    if (list && my_strncmp(element, list->env, my_strlen(element)) == 0) {
        temp = list;
        list = list->next;
        free(temp->env);
        free(temp);
        return list;
    }
    return list;
}

node_t *remove_element(node_t *list, char *element)
{
    node_t *temp = NULL;

    if (!list)
        return NULL;
    list = remove_first_element(list, element);
    for (node_t *current = list; current->env != NULL ||
        current->next != NULL; current = current->next) {
        if (!current->next)
            break;
        if (my_strncmp(element, current->next->env, my_strlen(element)) == 0) {
            temp = current->next;
            current->next = current->next->next;
            free(temp->env);
            free(temp);
            return list;
        }
    }
    return list;
}
