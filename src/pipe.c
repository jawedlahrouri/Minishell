/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle pipe
*/

#include "my.h"
#include "lib.h"

int create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
        return 1;
    return 0;
}

pid_t execute_first_command(char *cmd1, int pipefd[2], ssize_t r,
    char ***sh_env)
{
    pid_t pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        handle_redirections(cmd1);
        exit(handle_command(cmd1, r, sh_env));
    }
    return pid;
}

pid_t execute_second_command(char *cmd2, int pipefd[2], ssize_t r,
    char ***sh_env)
{
    pid_t pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        handle_redirections(cmd2);
        exit(handle_command(cmd2, r, sh_env));
    }
    return pid;
}

static int run_simple_command(char *command, ssize_t r, char ***sh_env)
{
    if (!my_strchr(command, '|')) {
        if (handle_redirections(command) != 1)
            return handle_command(command, r, sh_env);
        else
            return 1;
    }
    return -1;
}

static int validate_commands(char *cmd1, char *cmd2)
{
    if (!cmd1 || !cmd2 || my_strlen(cmd1) == 0 || my_strlen(cmd2) == 0) {
        my_printf("Invalid null command.\n");
        return 1;
    }
    return 0;
}

int setup_and_execute_pipe(char *cmd1, char *cmd2, ssize_t r, char ***sh_env)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;

    if (create_pipe(pipefd))
        return 1;
    pid1 = execute_first_command(cmd1, pipefd, r, sh_env);
    pid2 = execute_second_command(cmd2, pipefd, r, sh_env);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

static int handle_piped_commands(char *command, ssize_t r, char ***sh_env)
{
    char *cmd1 = strtok(command, "|");
    char *cmd2 = strtok(NULL, "|");
    int status = 0;

    if (validate_commands(cmd1, cmd2))
        return 1;
    status = setup_and_execute_pipe(cmd1, cmd2, r, sh_env);
    return status;
}

int handle_pipe(char *command, ssize_t r, char ***sh_env)
{
    int status = run_simple_command(command, r, sh_env);

    if (status != -1)
        return status;
    return handle_piped_commands(command, r, sh_env);
}
