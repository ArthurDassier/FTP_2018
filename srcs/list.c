/*
** EPITECH PROJECT, 2019
** list.c
** File description:
** list
*/

#include <dirent.h>
#include "server.h"

static void list_two(infos_t *infos, char **cmd)
{
    struct dirent   *file = NULL;
    DIR             *directory = NULL;
    int             fd = accept(infos->csock, NULL, NULL);

    send_reply(infos->csock, 150);
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
    closedir(directory);
    send_reply(infos->csock, 226);
    exit(0);
}

void list(infos_t *infos, char **cmd)
{
    pid_t child_pid;

    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] != NULL && cmd[2] != NULL)
        send_reply(infos->csock, 504);
    else {
        child_pid = fork();
        if (child_pid == 0)
            list_two(infos, cmd);
    }
}