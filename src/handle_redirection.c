/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle the redirections
*/

#include "my.h"
#include "lib.h"

static int handle_input_redir(char *command, int *saved_stdin)
{
    *saved_stdin = handle_input_redirection(command);
    if (*saved_stdin == 1)
        return 1;
    return 0;
}

static int handle_output_redir(char *command, int *saved_stdout)
{
    *saved_stdout = handle_output_redirection(command);
    if (*saved_stdout == 1)
        return 1;
    return 0;
}

static int handle_append_redir(char *command)
{
    return handle_append_redirection(command);
}

static void restore_descriptors(int saved_stdin, int saved_stdout)
{
    if (saved_stdin > 1) {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }
    if (saved_stdout > 1) {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
}

int handle_redirections(char *command)
{
    int saved_stdin = 0;
    int saved_stdout = 0;

    if (handle_input_redir(command, &saved_stdin))
        return 1;
    if (handle_output_redir(command, &saved_stdout)) {
        restore_descriptors(saved_stdin, 0);
        return 1;
    }
    if (handle_append_redir(command) != 0) {
        restore_descriptors(saved_stdin, saved_stdout);
        return 1;
    }
    return 0;
}
