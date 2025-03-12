/*
** EPITECH PROJECT, 2025
** lib
** File description:
** str_is_alnum
*/

int my_str_isalnum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= '0' && str[i] <= '9') ||
        str[i] == '/' || str[i] == '-' || str[i] == '.' ||
        str[i] == '|' || str[i] == ' ')
        return 1;
    }
    return 0;
}
