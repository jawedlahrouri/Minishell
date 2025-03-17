/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** command
*/

#include "my.h"
#include "lib.h"

char *create_bin(char *command)
{
    char *bin = malloc(sizeof(char) * (my_strlen(command) + 6));

    my_strcpy(bin, "/bin/");
    bin = my_strcat(bin, command);
    return bin;
}

char *get_path(char *command, char ***shell_env)
{
    char *bin = find_executable(command, shell_env);

    if (!bin && my_strncmp("/bin/", command, 5) == 0)
        return create_bin(command);
    return bin;
}

static pid_t create_process(char *bin, char **args, char ***shell_env)
{
    pid_t pid;

    if (access(bin, X_OK) != 0) {
        my_printf("%s: Permission denied.\n", bin);
        return -1;
    }
    pid = fork();
    if (pid == 0) {
        execve(bin, args, *shell_env);
        perror("execve failed");
        exit(1);
    }
    if (pid < 0)
        perror("fork failed");
    return pid;
}

static int wait_for_process(pid_t pid)
{
    int status;

    if (pid < 0)
        return 1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        my_putstr(strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            my_putstr(" (core dumped)\n");
        return 128 + WTERMSIG(status);
    }
    return 1;
}

static int run_command(char *bin, char **args, char ***shell_env)
{
    pid_t pid = create_process(bin, args, shell_env);

    return wait_for_process(pid);
}

int execute_command(char *command, char **args, char ***shell_env)
{
    char *bin = NULL;
    int status;

    if (my_strncmp(command, "./", 2) != 0)
        bin = get_path(command, shell_env);
    else
        bin = my_strdup(command);
    if (!bin || access(bin, F_OK) != 0) {
        my_printf("%s: Command not found.\n", command);
        return 127;
    }
    status = run_command(bin, args, shell_env);
    free(bin);
    return status;
}

int handle_command(char *buffer, ssize_t r, char ***sh_env, int exit_status)
{
    char **args = NULL;
    int built = 0;

    if (strncmp(buffer, "/bin ", 5) == 0 || strncmp(buffer, "/bin", 4) == 0) {
        printf("/bin: Permission denied.\n");
        return 1;
    }
    built = handle_builtin(buffer, r, sh_env, exit_status);
    if (built != 84)
        return built;
    if (my_strcmp(buffer, "\n") != 0 && my_strcmp(buffer, "env") != 0){
        args = my_str_to_word_array_advanced(buffer, "/-._|");
        return execute_command(args[0], args, sh_env);
    }
    return 0;
}
