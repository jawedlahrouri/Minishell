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
        return my_getenv(*shell_env, "HOME");
    if (my_strcmp(path, "-") == 0)
        return cd_previous_path(prev_dir);
    if (path[0] == '~' && path[1] != '\0') {
        cd_user_path(path);
        return NULL;
    }
    return path;
}

static int handle_cd_errors(char *path, char *command)
{
    if (my_strcmp(strtok(command, " "), "-") == 0)
        free(path);
    return 1;
}

int check_and_update_prev_dir(char **prev_dir, char *origin)
{
    free(*prev_dir);
    *prev_dir = origin;
    return 0;
}

int process_cd_path(char **path, char ***shell_env, char **prev_dir)
{
    *path = handle_cd_path(*path, shell_env, prev_dir);
    if (!*path || cd_handle_errors(*path))
        return 1;
    return 0;
}

int change_directory(char *path, char *command)
{
    if (chdir(path) != 0)
        return handle_cd_errors(path, command);
    return 0;
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
    if (process_cd_path(&path, shell_env, &prev_dir)) {
        free(origin);
        return 1;
    }
    if (change_directory(path, command)) {
        free(origin);
        return 1;
    }
    return check_and_update_prev_dir(&prev_dir, origin);
}
