/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my.h BOOTCAMP
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdint.h>
    #include <fcntl.h>
    #include <sys/wait.h>
    #include <limits.h>
    #include <string.h>
    #include <limits.h>
    #include <pwd.h>
    #include <sys/types.h>

/*Struct*/
typedef struct node {
    char *env;
    struct node *next;
} node_t;

/*Function*/
int main(int argc, char **argv, char **env);
int my_cd(char *command, char ***env);
int handle_command(char *buffer, ssize_t r, char ***sh_env);
char *find_executable(char *command, char ***env);
char *get_env_path(char ***env);
int handle_setenv(char *buffer, char ***env);
node_t *remove_element(node_t *list, char *element);
int handle_builtin(char *buffer, ssize_t r, char ***sh_env);
int execute_redirections(char *buffer, ssize_t r,
    char ***sh_env, int exit_status);
#endif /* !MY_H_ */
