/*
** EPITECH PROJECT, 2025
** minishell 2
** File description:
** handle cd builtin
*/

#include <sys/stat.h>
#include "lib.h"
#include "my.h"

static int cd_too_many_args(void)
{
    if (strtok(NULL, " ") != NULL) {
        my_printf("cd: Too many arguments.\n");
        return 1;
    }
    return 0;
}

static int cd_handle_errors(char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0) {
        my_printf("%s: No such file or directory.\n", path);
        return 1;
    }
    if (!S_ISDIR(path_stat.st_mode)) {
        my_printf("%s: Not a directory.\n", path);
        return 1;
    }
    if (access(path, X_OK) != 0) {
        my_printf("%s: Permission denied.\n", path);
        return 1;
    }
    return 0;
}

static char *cd_home_path(char ***shell_env)
{
    return my_getenv(*shell_env, "HOME");
}

static int cd_user_path(char *path)
{
    if (path[0] == '~' && path[1] != '\0') {
        my_printf("Unknown user: %s.\n", path + 1);
        return 1;
    }
    return 0;
}

static char *cd_previous_path(char **prev_dir)
{
    if (!*prev_dir) {
        my_printf(": No such file or directory.\n");
        return NULL;
    }
    return my_strdup(*prev_dir);
}

static char *handle_cd_path(char *path, char ***shell_env, char **prev_dir)
{
    if (!path || my_strcmp(path, "") == 0 || my_strcmp(path, "~") == 0)
        return cd_home_path(shell_env);
    if (my_strcmp(path, "-") == 0)
        return cd_previous_path(prev_dir);
    if (path[0] == '~' && path[1] != '\0') {
        cd_user_path(path);
        return NULL;
    }
    return path;
}

int my_cd(char *command, char ***shell_env)
{
    static char *prev_dir = NULL;
    char *origin = getcwd(NULL, 0);
    char *path = strtok(command, " ");

    path = strtok(NULL, " ");
    if (cd_too_many_args()) {
        free(origin);
        return 1;
    }
    path = handle_cd_path(path, shell_env, &prev_dir);
    if (!path || cd_handle_errors(path)) {
        free(origin);
        return 1;
    }
    if (chdir(path) != 0)
        return 1;
    free(prev_dir);
    prev_dir = origin;
    return 0;
}
