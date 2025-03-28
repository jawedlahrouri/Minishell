/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle redirections
*/

#include "lib.h"
#include "my.h"
#include <fcntl.h>
#include <unistd.h>

static int determine_redirection(const char *out_redir)
{
    int flags = O_WRONLY | O_CREAT;

    if (out_redir[1] == '>')
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    return flags;
}

static char *get_filename(char *out_redir)
{
    *out_redir = '\0';
    return strtok(out_redir + (out_redir[1] == '<' ? 2 : 1), " \t\n");
}

static int setup_output(const char *filename, int flags)
{
    int fd = open(filename, flags, 0644);

    if (fd == -1)
        return -1;
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

int handle_output_redirection(char *command)
{
    char *out_redir = my_strstr(command, ">");
    int saved_stdout = dup(STDOUT_FILENO);
    int flags;
    char *filename = NULL;

    if (!out_redir)
        return 0;
    flags = determine_redirection(out_redir);
    filename = get_filename(out_redir);
    if (!filename) {
        my_printf("Missing name for redirect.\n");
        return 1;
    }
    if (setup_output(filename, flags) == -1)
        return 1;
    return saved_stdout;
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

int handle_input_redirection(char *command)
{
    char *in_redir = my_strstr(command, "<");
    int saved_stdin = dup(STDIN_FILENO);
    char *filename = NULL;
    int fd = 0;

    if (!in_redir)
        return 0;
    filename = strtok(in_redir + 1, " \t\n");
    if (!filename) {
        my_printf("Missing filename for redirection.\n");
        return -1;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        my_printf("%s: No such file or directory\n", filename);
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return saved_stdin;
}
