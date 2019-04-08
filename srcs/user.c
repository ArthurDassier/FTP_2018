/*
** EPITECH PROJECT, 2019
** user.c
** File description:
** user
*/

#include "server.h"

void user(infos_t *infos, char **cmd)
{
    if (cmd[1] == NULL)
        send_reply(infos->csock, 504);
    else if (cmd[2] != NULL)
        send_reply(infos->csock, 504);
    else {
        if (strcmp(cmd[1], "Anonymous") == 0) {
            send_reply(infos->csock, 331);
            infos->user = KNOW;
        } else {
            send_reply(infos->csock, 331);
            infos->user = UNKNOW;
        }
    }
}

void password(infos_t *infos, char **cmd)
{
    if (cmd[1] != NULL && strcmp(cmd[1], " ") != 0)
        if (cmd[2] != NULL)
            send_reply(infos->csock, 504);
        else
            send_reply(infos->csock, 530);
    else {
        if (infos->user == NOT_LOGGED) {
            send_reply(infos->csock, 503);
        } else if (infos->user == KNOW) {
            send_reply(infos->csock, 230);
            infos->pwd = true;
        } else
            send_reply(infos->csock, 530);
    }
}