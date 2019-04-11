/*
** EPITECH PROJECT, 2019
** passive.c
** File description:
** passive
*/

#include "server.h"

static void server_reply(infos_t *infos, char *ip, int port1, int port2)
{
    infos->state = PASSIVE;
    send_reply(infos->csock, 227);
    for (int i = 0; ip[i] != '\0'; ++i) {
        if (ip[i] == '.')
            ip[i] = ',';
    }
    dprintf(infos->csock, "%s", ip);
    dprintf(infos->csock, ",%d,%d).\n", port1, port2);
}

static void passive_mode(infos_t *infos, __attribute__((unused)) char **cmd)
{
    sockaddr_in_t   sin = infos->csin;
    socklen_t       recsize = sizeof(sin);
    int_socket      psock = socket(AF_INET, SOCK_STREAM, 0);
    char            *ip = inet_ntoa(infos->csin.sin_addr);
    int             port1 = ((random() % 255) * 256);
    int             port2 = (random() % 255);

    sin.sin_port = port1 + port2;
    if (psock == -1)
        return;
    if (bind(psock, (sockaddr_t*)&sin, recsize) == -1)
        return;
    if (listen(psock, 5) == -1)
        return;
    server_reply(infos, ip, port1, port2);
}

void pasv(infos_t *infos, __attribute__((unused)) char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else
        passive_mode(infos, cmd);
}