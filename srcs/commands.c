/*
** EPITECH PROJECT, 2019
** commands.c
** File description:
** commands
*/

#include "server.h"

void noop(t_infos *infos, char **cmd)
{
    if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else
        send_reply(infos->csock, 200);
}

void pwd(t_infos *infos, char **cmd)
{
    char *tmp = NULL;

    if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else
        dprintf(infos->csock, "257 \"/%s\"\r\n", getcwd(tmp, 200));
}

void cdup(t_infos *infos, char **cmd)
{
    if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else {
        if (chdir("..") == -1)
            send_reply(infos->csock, 550);
        else
            send_reply(infos->csock, 200);
    }
}

void cwd(t_infos *infos, char **cmd)
{
    if (cmd[1] == NULL || cmd[2] != NULL)
        send_reply(infos->csock, 504);
    else if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else {
        if (chdir(cmd[1]) == -1)
            send_reply(infos->csock, 550);
        else
            send_reply(infos->csock, 200);
    }
}