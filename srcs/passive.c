/*
** EPITECH PROJECT, 2019
** passive.c
** File description:
** passive
*/

#include "server.h"

static void server_reply(t_infos *infos, char *ip, int port1, int port2)
{
    infos->state = PASSIVE;
    send_reply(infos->csock, 227);
    for (int i = 0; ip[i] != '\0'; ++i) {
        if (ip[i] == '.')
            ip[i] = ',';
    }
    dprintf(infos->csock, "%s", ip);
    dprintf(infos->csock, ",%d,%d)\n", port1, port2);
}

static void passive_mode(t_infos *infos, __attribute__((unused)) char **cmd)
{
    SOCKADDR_IN     sin = infos->csin;
    socklen_t       recsize = sizeof(sin);
    SOCKET          psock = socket(AF_INET, SOCK_STREAM, 0);
    char            *ip = inet_ntoa(infos->csin.sin_addr);
    int             port1 = ((random() % 255) * 256);
    int             port2 = (random() % 255);

    sin.sin_port = port1 + port2;
    if (psock == -1)
        return;
    if (bind(psock, (SOCKADDR*)&sin, recsize) == -1)
        return;
    if (listen(psock, 5) == -1) 
        return;
    infos->psock = accept(psock, (SOCKADDR*)&sin, &recsize);
    server_reply(infos, ip, port1, port2);
}

void pasv(t_infos *infos, __attribute__((unused)) char **cmd)
{
    if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else
        passive_mode(infos, cmd);
}