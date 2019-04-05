/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "server.h"

int add_node(t_infos **basic, SOCKET csock, SOCKADDR_IN csin, char *home)
{
    t_infos *infos = malloc(sizeof(t_infos));
    t_infos *tmp = (*basic);

    if (infos == NULL)
        return (84);
    infos->csock = csock;
    infos->csin = csin;
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

int delete_node(t_infos **infos, t_infos *to_delete, fd_set *active_fd_set)
{
    t_infos *tmp = (*infos);

    if (tmp == NULL)
        return (84);
    FD_CLR(to_delete->csock, active_fd_set);
    while (tmp->next != NULL) {
        if (tmp->csock == to_delete->csock)
            break;
        tmp = tmp->next;
    }
    tmp = to_delete->next;
    send_reply(to_delete->csock, 221);
    close(to_delete->csock);
    free(to_delete);
    return (0);
}