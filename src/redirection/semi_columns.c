/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle semi_columns
*/

#include "my.h"
#include "lib.h"

static void free_exit_shell(char **tab, int exit_status)
{
    free(tab);
    exit(exit_status);
}

static void my_exit(char *buffer, int exit_status)
{
    char **tab = my_str_to_word_array(buffer);

    if (!tab[0]) {
        free(tab);
        return;
    }
    if (my_strcmp(tab[0], "exit") == 0) {
        if (tab[1] && tab[1][0] == '|') {
            free(tab);
            return;
        }
        if (!tab[1]) {
            my_printf("exit\n");
            free_exit_shell(tab, exit_status);
        } else {
            my_printf("exit: Expression Syntax.\n");
            free(tab);
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

static int process_command(char *command, ssize_t r, char ***sh_env, int *exit)
{
    int saved_stdin = dup(STDIN_FILENO);
    int redir_status = handle_input_redirection(command);
    int status = 0;

    if (redir_status == -1)
        status = 1;
    else
        status = handle_pipe(command, r, sh_env);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    *exit = (status != 0) ? status : *exit;
    return status;
}

static int handle_empty_buffer(char *buffer, ssize_t r, char *buffer_copy)
{
    if (empty_line_handling(buffer, r) == 0) {
        free(buffer_copy);
        return 1;
    }
    return 0;
}

static int process_command_loop(char *buffer_copy, ssize_t r,
    char ***sh_env, int *exit)
{
    char *command = NULL;
    char *saveptr = NULL;
    int status = 0;

    command = strtok_r(buffer_copy, ";", &saveptr);
    while (command != NULL) {
        my_exit(command, *exit);
        if (*command != '\0')
            status = process_command(command, r, sh_env, exit);
        command = strtok_r(NULL, ";", &saveptr);
    }
    return status;
}

int execute_redirections(char *buffer, ssize_t r, char ***sh_env, int exit)
{
    char *buffer_copy = my_strdup(buffer);

    if (!buffer_copy)
        return exit;
    if (handle_empty_buffer(buffer, r, buffer_copy))
        return 0;
    process_command_loop(buffer_copy, r, sh_env, &exit);
    free(buffer_copy);
    return exit;
}
