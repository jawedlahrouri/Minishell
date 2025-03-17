/*
** EPITECH PROJECT, 2025
** mini shell 1
** File description:
** handle cd command in the shell
*/

#include "lib.h"
#include "my.h"

int handle_cd_dash(char **path, char **prev_dir)
{
    if (*prev_dir) {
        *path = my_strdup(*prev_dir);
        return 0;
    } else {
        my_printf(": No such file or directory.\n");
        return 1;
    }
}

int my_cd(char *command, char ***shell_env)
{
    static char *prev_dir = NULL;
    char *origin = getcwd(NULL, 0);
    char *path = strtok(command, " ");

    path = strtok(NULL, " ");
    if (!path || my_strcmp(path, "") == 0 || my_strcmp(path, "~") == 0) {
        path = my_getenv(*shell_env, "HOME");
    } else if (my_strcmp(path, "-") == 0) {
        handle_cd_dash(&path, &prev_dir);
        chdir(path);
        return 0;
    }
    if (path && chdir(path) != 0) {
        my_printf("%s: No such file or directory.\n", path);
        return 1;
    } else {
        if (prev_dir)
            free(prev_dir);
        prev_dir = origin;
    }
    return 0;
}
