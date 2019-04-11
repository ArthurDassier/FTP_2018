/*
** EPITECH PROJECT, 2019
** stor.c
** File description:
** stor
*/

#include "server.h"

static void stor_two(infos_t *infos, char **cmd)
{
    char    boeuf[1];
    int     file_open = open(cmd[1], O_CREAT | O_TRUNC | O_RDWR, 0666);
    int     fd_write = accept(infos->csock, NULL, NULL);

    while (read(fd_write, boeuf, 1) > 0)
        write(file_open, boeuf, 1);
    send_reply(infos->csock, 226);
    close(file_open);
    close(infos->psock);
    infos->state = NORMAL;
    exit(0);
}

void stor(infos_t *infos, char **cmd)
{
    pid_t child_pid;

    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    if (cmd[1] == NULL || cmd[2] != NULL) {
        send_reply(infos->csock, 504);
        return;
    }
    if (infos->state == NORMAL) {
        send_reply(infos->csock, 425);
        return;
    }
    child_pid = fork();
    if (child_pid == 0)
        stor_two(infos, cmd);
}

void dele(infos_t *infos, __attribute__((unused)) char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else
        send_reply(infos->csock, 250);
}