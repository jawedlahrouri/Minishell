/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle redirections
*/

#include "lib.h"
#include "my.h"

int handle_input_redirection(char *command)
{
    char *in_redir = my_strchr(command, '<');
    int fd = -1;
    char *file = NULL;

    if (!in_redir)
        return 0;
    *in_redir = '\0';
    file = strtok(in_redir + 1, " ");
    if (!file)
        return 1;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return 1;
    dup2(fd, STDIN_FILENO);
    close(fd);
    return 0;
}

int handle_output_redirection(char *command)
{
    char *out_redir = my_strchr(command, '>');
    int fd = -1;
    char *file = NULL;

    if (!out_redir || out_redir[1] == '>')
        return 0;
    *out_redir = '\0';
    file = strtok(out_redir + 1, " ");
    if (!file)
        return 1;
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return 1;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int handle_append_redirection(char *command)
{
    char *append_redir = my_strstr(command, ">>");
    char *file = NULL;
    int fd = -1;

    if (!append_redir)
        return 0;
    *append_redir = '\0';
    file = strtok(append_redir + 2, " ");
    if (!file)
        return 1;
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        return 1;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int handle_redirections(char *command)
{
    if (handle_input_redirection(command) != 0)
        return 1;
    if (handle_output_redirection(command) != 0)
        return 1;
    if (handle_append_redirection(command) != 0)
        return 1;
    return 0;
}
