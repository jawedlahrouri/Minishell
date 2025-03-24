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
        if (tab[1] && tab[1][0] == '|') {
            return;
        }
        if (!tab[1]) {
            my_printf("exit\n");
            exit(exit_status);
        } else {
            my_printf("exit: Expression Syntax.\n");
            exit(1);
        }
    }
}

int create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    return 0;
}

pid_t execute_first_command(char *cmd1, int pipefd[2], ssize_t r,
    char ***sh_env)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }
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

    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        handle_redirections(cmd2);
        exit(handle_command(cmd2, r, sh_env));
    }
    return pid;
}

int handle_pipe(char *command, ssize_t r, char ***sh_env)
{
    char *cmd1 = strtok(command, "|");
    char *cmd2 = strtok(NULL, "|");
    int pipefd[2];
    pid_value_t *pids;

    if (!my_strchr(command, '|') || !command)
        return handle_command(command, r, sh_env);
    if (!cmd1 || !cmd2 || my_strlen(cmd1) == 0 || my_strlen(cmd2) == 0) {
        my_printf("Invalid null command.\n");
        return 1;
    }
    if (create_pipe(pipefd))
        return 1;
    pids->pid1 = execute_first_command(cmd1, pipefd, r, sh_env);
    pids->pid2 = execute_second_command(cmd2, pipefd, r, sh_env);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pids->pid1, NULL, 0);
    waitpid(pids->pid2, NULL, 0);
    return 0;
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
