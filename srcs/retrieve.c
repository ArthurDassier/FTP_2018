/*
** EPITECH PROJECT, 2019
** retrieve.c
** File description:
** retrieve
*/

#include "server.h"

void retr_two(infos_t *infos, char **cmd)
{
    FILE    *file;
    int     fd;
    char    c = '\0';

    file = fopen(cmd[1], "r");
    if (!file) {
        send_reply(infos->csock, 550);
        return;
    }
    fd = accept(infos->psock, NULL, NULL);
    while ((c = fgetc(file)) != EOF)
        dprintf(fd, "%c", c);
    send_reply(infos->csock, 226);
    close(fd);
    close(infos->psock);
    infos->state = NORMAL;
    exit(0);
}

void retr(infos_t *infos, char **cmd)
{
    pid_t child_pid;

    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    } else if (cmd[1] == NULL || cmd[2] != NULL) {
        send_reply(infos->csock, 504);
        return;
    }
    if (infos->state == NORMAL) {
        send_reply(infos->csock, 425);
        return;
    }
    child_pid = fork();
    if (child_pid == 0)
        retr_two(infos, cmd);
}