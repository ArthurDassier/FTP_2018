/*
** EPITECH PROJECT, 2019
** help.c
** File description:
** help
*/

#include "server.h"

void help(infos_t *infos, char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    if (cmd[1] == NULL)
        send_reply(infos->csock, 214);
    else if (cmd[2] == NULL)
        send_reply(infos->csock, 214);
    else
        send_reply(infos->csock, 504);
}