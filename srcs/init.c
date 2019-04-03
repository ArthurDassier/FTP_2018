/*
** EPITECH PROJECT, 2019
** init.c
** File description:
** init
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

SOCKADDR_IN init_sock_addr(int port)
{
    SOCKADDR_IN     sin;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    return (sin);
}

SOCKET init_socket(int port)
{
    SOCKADDR_IN     sin;
    socklen_t       recsize = sizeof(sin);
    SOCKET          sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("Error on socket");
        return (84);
    }
    sin = init_sock_addr(port);
    if (bind(sock, (SOCKADDR*)&sin, recsize) == -1) {
        perror("Error on bind");
        return (84);
    }
    if (listen(sock, 5) == -1) {
        perror("Error on listen");
        return (84);
    }
    return (sock);
}