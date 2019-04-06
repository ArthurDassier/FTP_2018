/*
** EPITECH PROJECT, 2018
** my_str_to_wordtab.c
** File description:
** Arthur
*/

#include "server.h"

static int count_word(char *str)
{
    int word = 0;
    int letter = 0;
    int i = 0;

    while (str[i] != '\0') {
        if ((str[i] != ' ' && str[i] != '\t') && letter == 0) {
            ++word;
            letter = 1;
        }
        if ((str[i] == ' ' || str[i] == '\t') && letter == 1)
            letter = 0;
        ++i;
    }
    return (word);
}

static char *clean_str(char *str)
{
    char    *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int     j = 0;
    int     space = 1;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ' && str[i] != '\t') {
            tmp[j] = str[i];
            space = 0;
            ++j;
        } else if ((str[i] == ' ' || str[i] == '\t') && space == 0) {
            tmp[j] = str[i];
            ++j;
            space = 1;
        }
    }
    tmp[j] = '\0';
    if (tmp[--j] == ' ' || tmp[j] == '\t')
        tmp[j] = '\0';
    return (tmp);
}

char **my_str_to_wordtab(char *str)
{
    char    **tab = malloc(sizeof(char *) * (count_word(str) + 1));
    int     j = 0;
    int     col = 0;

    str = clean_str(str);
    tab[col] = malloc(sizeof(char) * (strlen(str) + 1));
    for (int i = 0; str[i] != '\0' && str[i] != '\r'; ++i) {
        if (str[i] == ' ') {
            tab[col][j] = '\0';
            ++col;
            j = 0;
            ++i;
            tab[col] = malloc(sizeof(char) * (strlen(str) + 1));
        }
        tab[col][j] = str[i];
        ++j;
    }
    tab[col][j] = '\0';
    tab[++col] = NULL;
    return (tab);
}
