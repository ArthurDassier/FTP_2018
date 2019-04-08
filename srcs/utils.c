/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "server.h"

int add_node(infos_t **basic, SOCKET csock, SOCKADDR_IN csin, char *home)
{
    infos_t *infos = malloc(sizeof(infos_t));
    infos_t *tmp = (*basic);

    if (infos == NULL)
        return (84);
    infos->csock = csock;
    infos->csin = csin;
    infos->user = false;
    infos->pwd = false;
    infos->home = strdup(home);
    infos->next = NULL;
    infos->construct = malloc(sizeof(char) * 20);
    infos->constru = 0;
    if (tmp != NULL) {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = infos;
    } else
        *basic = infos;
    return (0);
}

int delete_node(infos_t **infos, infos_t *to_delete, fd_set *active_fd_set)
{
    infos_t *tmp = (*infos);

    if (tmp == NULL)
        return (84);
    while (tmp->next != NULL) {
        if (tmp->csock == to_delete->csock)
            break;
        tmp = tmp->next;
    }
    send_reply(to_delete->csock, 221);
    FD_CLR(to_delete->csock, active_fd_set);
    close(to_delete->csock);
    if (to_delete->next != NULL) {
        tmp = to_delete->next;
        free(to_delete);
    }
    return (0);
}
