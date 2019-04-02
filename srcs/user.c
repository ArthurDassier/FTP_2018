/*
** EPITECH PROJECT, 2019
** user.c
** File description:
** user
*/

#include "server.h"

void user(SOCKET csock, char **cmd)
{
    if (cmd[1] == NULL)
        send_reply(csock, 504);
    else if (cmd[2] != NULL)
        send_reply(csock, 504);
    else {
        if (strcmp(cmd[1], "Anonymous") == 0)
            send_reply(csock, 331);
        else
            send_reply(csock, 331);
    }
}

void password(SOCKET csock, char **cmd)
{
    if (cmd[1] == NULL)
        send_reply(csock, 504);
    else if (cmd[2] != NULL)
        send_reply(csock, 504);
    else {
        if (strcmp(cmd[1], "") == 0)
            send_reply(csock, 230);
        else
            send_reply(csock, 530);
    }
}