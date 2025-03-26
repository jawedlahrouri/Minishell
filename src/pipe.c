/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle redirections
*/

#include "my.h"
#include "lib.h"

static void my_exit(char *buffer, int exit_status)
{
    char **tab = my_str_to_word_array(buffer);

    if (!tab[0])
        return;
    if (my_strcmp(tab[0], "exit") == 0) {
        if (tab[1] && tab[1][0] == '|')
            return;
        if (!tab[1]) {
            my_printf("exit\n");
            exit(exit_status);
        } else {
            my_printf("exit: Expression Syntax.\n");
            exit(1);
        }
    }
}

static int empty_line_handling(char *buffer, ssize_t r)
{
    if (my_str_isalnum(buffer) == 0 || is_only_spaces(buffer))
        return 0;
    else if (my_strcmp(buffer, "\n") != 0)
        buffer[r - 1] = '\0';
    return 84;
}

int execute_redirections(char *buffer, ssize_t r, char ***sh_env, int exit)
{
    char *command = NULL;
    char *buffer_copy = my_strdup(buffer);
    char *saveptr = NULL;
    int status = 0;

    if (empty_line_handling(buffer, r) == 0)
        return 0;
    if (!buffer_copy)
        return exit;
    command = strtok_r(buffer_copy, ";", &saveptr);
    while (command != NULL) {
        my_exit(command, exit);
        if (*command != '\0') {
            handle_redirections(command);
            status = handle_pipe(command, r, sh_env);
            exit = (status != 0) ? status : exit;
        }
        command = strtok_r(NULL, ";", &saveptr);
    }
    return exit;
}
