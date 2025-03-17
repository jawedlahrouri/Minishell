/*
** EPITECH PROJECT, 2024
** Mon H
** File description:
** Header avec les fonctions
*/

#ifndef LIB_H
    #define LIB_H

    #include <stdio.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dirent.h>
    #include <time.h>
    #include <unistd.h>

// Flags pour printf
void flag_c(va_list list);
void flag_d(va_list list);
void flag_i(va_list list);
void flag_o(va_list list);
void flag_percent(va_list list);
void flag_s(va_list list);
void flag_x(va_list list);
void flag_x2(va_list list);

// Fonctions mathématiques
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_getnbr(const char *str);
int my_isneg(int nb);
int my_atoi(const char *str);

// Fonctions d'affichage
int my_printf(const char *format, ...);
int my_put_nbr(int nb);
void my_putchar(char c);
void my_putstr(char const *str);

// Fonctions de manipulation de chaînes
char *my_revstr(char *str);
int my_str_isnum(char const *str);
char **my_str_to_word_array(char *str);
char **my_str_to_word_array_advanced(char *str, char *extra_chars);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char *const str1, char *const str2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
char *my_strncat(char *dest, const char *src, size_t n);
int my_strncmp(char const *s1, char const *s2, size_t n);
char *my_strncpy(char *dest, char const *src, int n);
int my_strmajcmp(char *str1, char *str2);
int my_strnmajcmp(char *str1, char *str2, int n);
int my_str_tolower(char *str);
char *my_strchr(const char *str, char c);
char *my_strtok(char *str, const char *delim);
char *extract_str(char const *str, char separator);
char *extract_str_advanced(char *str, char separator1, char separator2);
char **my_copy_word_in_array(char **tab);

// Fonctions utilitaires
void my_swap(int *a, int *b);
int bubble_sort(char **tab);
void my_show_word_in_array(char **tab);
char *my_getenv(char **env, char *value);
void my_free_word_array(char **tab);
void free_array(char **tab);

// Fonctions de vérification de caractères
int my_isalpha(char c);
int my_isdigit(char c);
int my_str_isalnum(char *str);
int my_strisalnum(char *str);

#endif /*lib.h*/
