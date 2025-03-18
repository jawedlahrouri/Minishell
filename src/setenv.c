/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** setenv and unsetenv file
*/

#include "lib.h"
#include "my.h"

node_t *add_to_list(node_t *list, const char *new_entry)
{
    node_t *new_node = malloc(sizeof(node_t));
    node_t *temp;

    if (!new_node)
        return list;
    new_node->env = my_strdup(new_entry);
    new_node->next = NULL;
    if (!list)
        return new_node;
    temp = list;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
    return list;
}

static node_t *env_to_list(char **env)
{
    node_t *head = NULL;
    node_t *tail = NULL;
    node_t *new_node = NULL;

    for (int i = 0; env[i]; i++) {
        new_node = malloc(sizeof(node_t));
        if (!new_node)
            return NULL;
        new_node->env = my_strdup(env[i]);
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            tail->next = new_node;
        tail = new_node;
    }
    return head;
}

static node_t *update_or_add(node_t *list, char *key, char *value)
{
    node_t *temp = list;
    int len = my_strlen(key);
    char *new_entry = malloc(len + my_strlen(value) + 2);

    if (!new_entry)
        return list;
    my_strcpy(new_entry, key);
    my_strcat(new_entry, "=");
    my_strcat(new_entry, value);
    while (temp) {
        if (my_strncmp(temp->env, key, len) == 0 && temp->env[len] == '=') {
            free(temp->env);
            temp->env = new_entry;
            return list;
        }
        if (!temp->next)
            break;
        temp = temp->next;
    }
    return add_to_list(list, new_entry);
}

static char **list_to_env(node_t *list)
{
    int size = 0;
    char **env = NULL;
    node_t *temp = list;

    while (temp) {
        size++;
        temp = temp->next;
    }
    env = malloc(sizeof(char *) * (size + 1));
    if (!env)
        return NULL;
    for (int i = 0; list; list = list->next) {
        env[i] = my_strdup(list->env);
        i++;
    }
    env[size] = NULL;
    return env;
}

int setenv_error_handling(char **tab, char ***shell_env, int nbr)
{
    if (!tab[1]) {
        my_show_word_in_array(*shell_env);
        return 1;
    } else if (my_isalpha(tab[1][0]) == 1) {
        my_printf("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (my_strisalnum(tab[1]) == 0) {
        my_printf("setenv: Variable name must ");
        my_printf("contain alphanumeric characters.\n");
        return 1;
    } else if (3 < nbr) {
        my_printf("setenv: Too many arguments.\n");
        return 1;
    }
    return 0;
}

static int count_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

int my_setenv(char *command, char ***shell_env)
{
    char **tab = my_str_to_word_array_advanced(command,
        "_:/.+-*@#%&(){}[]|\\^~!?<>=\"");
    node_t *list = env_to_list(*shell_env);
    int nbr = count_tab(tab);

    if (setenv_error_handling(tab, shell_env, nbr) == 1)
        return 1;
    if (tab[1] && !tab[2]) {
        list = update_or_add(list, tab[1], "");
        *shell_env = list_to_env(list);
        free_array(tab);
        return 0;
    }
    list = update_or_add(list, tab[1], tab[2]);
    *shell_env = list_to_env(list);
    free_array(tab);
    return 0;
}

int my_unsetenv(char *command, char ***shell_env)
{
    char **tab = my_str_to_word_array_advanced(command, "/-._|");
    node_t *list = env_to_list(*shell_env);

    if (tab[2])
        return 0;
    if (!tab[1]) {
        my_printf("unsetenv: Too few arguments.\n");
        return 1;
    }
    list = remove_element(list, tab[1]);
    *shell_env = list_to_env(list);
    free_array(tab);
    return 0;
}

int handle_setenv(char *buffer, char ***shell_env)
{
    int exit_status = 0;

    if (!*shell_env)
        return 84;
    if (my_strncmp(buffer, "setenv", 6) == 0) {
        exit_status = my_setenv(buffer, shell_env);
        return exit_status;
    } else if (my_strncmp(buffer, "unsetenv", 8) == 0) {
        exit_status = my_unsetenv(buffer, shell_env);
        return exit_status;
    }
    if (my_strcmp(buffer, "env") == 0) {
        my_show_word_in_array(*shell_env);
        return 0;
    }
    return 84;
}
