/*
** EPITECH PROJECT, 2025
** lib
** File description:
** str_isalnum
*/

int my_strisalnum(char *str)
{
    if (!str || str[0] == '\0')
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9')))
            return 0;
    }
    return 1;
}