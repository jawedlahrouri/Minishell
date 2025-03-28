/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** builtin handling
*/

#include "lib.h"
#include "my.h"

int is_only_spaces(char *buffer)
{
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n')
            return 0;
    }
    return 1;
}

int handle_builtin(char *buffer, ssize_t r, char ***sh_env)
{
    int built = 0;

    if (my_str_isalnum(buffer) == 0 || is_only_spaces(buffer))
        return 0;
    else if (my_strcmp(buffer, "\n") != 0)
        buffer[r - 1] = '\0';
    if (my_strncmp(buffer, "cd", 2) == 0)
        return my_cd(buffer, sh_env);
    built = handle_setenv(buffer, sh_env);
        return built;
    return 84;
}
