/*
** EPITECH PROJECT, 2025
** mini_shell 1
** File description:
** main file
*/

#include "my.h"
#include "lib.h"

#include <unistd.h>

static void display_prompt(int saved_stdout)
{
    if (isatty(STDOUT_FILENO)) {
        dup2(saved_stdout, STDOUT_FILENO);
        write(STDOUT_FILENO, "$> ", 3);
    }
}

int open_terminal(char ***sh_env)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t r = 0;
    int exit_status = 0;
    int saved_stdout = dup(STDOUT_FILENO);

    while (1) {
        display_prompt(saved_stdout);
        r = getline(&buffer, &len, stdin);
        if (r == -1) {
            write(STDOUT_FILENO, "exit\n", 5);
            close(saved_stdout);
            free(buffer);
            return exit_status;
        }
        exit_status = execute_redirections(buffer, r, sh_env, exit_status);
        dup2(saved_stdout, STDOUT_FILENO);
    }
}

int open_non_terminal(char ***sh_env)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t r = 0;
    int exit_status = 0;

    while (1) {
        r = getline(&buffer, &len, stdin);
        if (r == -1) {
            return exit_status;
        } else
            exit_status = execute_redirections(buffer, r, sh_env, exit_status);
        if (exit_status != 0)
            break;
    }
    free(buffer);
    return exit_status;
}

int main(int argc, char **argv, char **env)
{
    int status = 1;
    char ***shell_env = malloc(sizeof(char **) * 2);

    if (argc > 1 || argv[1] || !env)
        return 84;
    *shell_env = my_copy_word_in_array(env);
    if (!*shell_env)
        return 84;
    if (isatty(STDIN_FILENO) == 1)
        status = open_terminal(shell_env);
    else
        status = open_non_terminal(shell_env);
    if (status > 100) {
        my_free_word_array(*shell_env);
        return 1;
    } else {
        free_array(*shell_env);
        return status;
    }
}
