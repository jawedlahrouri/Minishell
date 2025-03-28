/*
** EPITECH PROJECT, 2025
** minishell 1
** File description:
** the function that search and find the path
*/

#include "my.h"
#include "lib.h"

char *get_env_path(char ***shell_env)
{
    if (!shell_env || !*shell_env)
        return NULL;
    for (int i = 0; (*shell_env)[i]; i++) {
        if (my_strncmp((*shell_env)[i], "PATH=", 5) == 0)
            return (*shell_env)[i] + 5;
    }
    return NULL;
}

char *build_path(char *dir, char *command)
{
    int len_path = my_strlen(dir);
    int len_cmd = my_strlen(command);
    char *full_path = malloc(len_path + len_cmd + 2);

    if (!full_path)
        return NULL;
    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, command);
    return full_path;
}

char *search_in_paths(char *paths, char *command)
{
    char *token = strtok(paths, ":");
    char *full_path = NULL;

    while (token) {
        full_path = build_path(token, command);
        if (!full_path)
            break;
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        token = strtok(NULL, ":");
    }
    return NULL;
}

char *find_executable(char *command, char ***shell_env)
{
    char *paths = get_env_path(shell_env);
    char *paths_copy = NULL;
    char *full_path = NULL;

    if (!paths)
        return NULL;
    if (my_strncmp(command, "/bin/", 5) == 0)
        return my_strdup(command);
    paths_copy = my_strdup(paths);
    full_path = search_in_paths(paths_copy, command);
    free(paths_copy);
    return full_path;
}
