/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** transform env to a list
*/

#include "lib.h"
#include "my.h"

static void free_env_list(node_t *head)
{
    node_t *tmp = NULL;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->env);
        free(tmp);
    }
}

static node_t *create_node(const char *env_str)
{
    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node)
        return NULL;
    new_node->env = my_strdup(env_str);
    if (!new_node->env) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

static void append_node(node_t **head, node_t **tail, node_t *new_node)
{
    if (!*head)
        *head = new_node;
    else
        (*tail)->next = new_node;
    *tail = new_node;
}

node_t *env_to_list(char **env)
{
    node_t *head = NULL;
    node_t *tail = NULL;
    node_t *new_node = NULL;

    for (int i = 0; env[i]; i++) {
        new_node = create_node(env[i]);
        if (!new_node) {
            free_env_list(head);
            return NULL;
        }
        append_node(&head, &tail, new_node);
    }
    return head;
}
