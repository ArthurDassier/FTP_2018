/*
** EPITECH PROJECT, 2019
** list.c
** File description:
** list
*/

#include <dirent.h>
#include "server.h"

static void list_fork(infos_t *infos, char **cmd)
{
    struct dirent   *file = NULL;
    DIR             *directory = NULL;
    int             fd = accept(infos->psock, NULL, NULL);

    dprintf(fd, "150 ");
    if (cmd[1] != NULL)
        directory = opendir(cmd[1]);
    else
        directory = opendir(".");
    if (!directory)
        send_reply(infos->csock, 550);
    while ((file = readdir(directory))) {
        if (file->d_name[0] != '.')
            dprintf(fd, "%s\n", file->d_name);
    }
    dprintf(fd, "\r\n");
    closedir(directory);
    send_reply(infos->csock, 226);
    exit(0);
}

void list(infos_t *infos, char **cmd)
{
    pid_t child_pid;

    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    if (cmd[1] != NULL && cmd[2] != NULL) {
        send_reply(infos->csock, 504);
        return;
    }
    if (infos->state == NORMAL) {
        send_reply(infos->csock, 425);
        return;
    }
    child_pid = fork();
    if (child_pid == 0)
        list_fork(infos, cmd);
}