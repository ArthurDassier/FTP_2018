/*
** EPITECH PROJECT, 2019
** stor.c
** File description:
** stor
*/

#include "server.h"

void stor_two(t_infos *infos, char **cmd)
{
    char    boeuf[1];
    int     file_open;
    int     fd_write;

    file_open = open(cmd[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
    fd_write = accept(infos->csock, NULL, NULL);
    send_reply(infos->csock, 150);
    while (read(fd_write, boeuf, 1) > 0)
        write(file_open, boeuf, 1);
    send_reply(infos->csock, 226);
    close(file_open);
    close(infos->psock);
    infos->state = NORMAL;
}

void stor(t_infos *infos, char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    if (cmd[1] == NULL) {
        send_reply(infos->csock, 504);
        return;
    }
    if (cmd[2] != NULL) {
        send_reply(infos->csock, 504);
        return;
    }
    stor_two(infos, cmd);
}
