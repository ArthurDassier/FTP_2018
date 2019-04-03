/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "server.h"

int add_node(t_infos **basic, SOCKET csock, char *home)
{
    t_infos *infos = malloc(sizeof(t_infos));
    t_infos *tmp = (*basic);

    if (infos == NULL)
        return (84);
    infos->csock = csock;
    infos->user = false;
    infos->pwd = false;
    infos->home = strdup(home);
    infos->next = NULL;
    if (tmp != NULL) {
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = infos;
    } else
        *basic = infos;
    return (0);
}