/*
** EPITECH PROJECT, 2025
** mini_shell 1
** File description:
** main file
*/

#include "my.h"
#include "lib.h"

static void my_exit(char *buffer, int exit_status)
{
    if (my_strcmp(buffer, "exit") == 0) {
        my_printf("exit\n");
        exit(exit_status);
    }
    if (my_strncmp(buffer, "exit", 4) == 0) {
        my_printf("exit: Expression Syntax.\n");
        exit(1);
    }
}

int execute_redirections(char *buffer, ssize_t r,
    char ***sh_env, int exit_status)
{
    char *command = NULL;
    char *buffer_copy = my_strdup(buffer);
    char *saveptr = NULL;
    int status = 0;

    if (!buffer_copy)
        return exit_status;
    command = strtok_r(buffer_copy, ";", &saveptr);
    while (command != NULL) {
        my_exit(command, exit_status);
        if (*command != '\0') {
            status = handle_command(command, r, sh_env, exit_status);
            exit_status = (status != 0) ? status : exit_status;
        }
        command = strtok_r(NULL, ";", &saveptr);
    }
    free(buffer_copy);
    return exit_status;
}

int open_terminal(char ***sh_env)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t r = 0;
    int exit_status = 0;

    while (1) {
        my_printf("$> ");
        r = getline(&buffer, &len, stdin);
        if (r == -1) {
            my_printf("exit\n");
            return exit_status;
        } else
            exit_status = execute_redirections(buffer, r, sh_env, exit_status);
    }
    free(buffer);
    return exit_status;
}

int open_non_terminal(char ***shell_env)
{
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int exit_status = 0;

    while (1) {
        read = getline(&buffer, &len, stdin);
        if (read == -1) {
            return exit_status;
        } else
            exit_status = handle_command(buffer, read, shell_env, exit_status);
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
        my_free_word_array(*shell_env);
        return status;
    }
}
