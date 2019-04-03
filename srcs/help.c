/*
** EPITECH PROJECT, 2019
** help.c
** File description:
** help
*/

#include "server.h"

static void help_two(SOCKET csock)
{
    dprintf(csock, "PWD  <CRLF>                   : \
    Print working directory\n");
    dprintf(csock, "PASV <CRLF>                   : \
    Enable 'passive' mode for data transfer\n");
    dprintf(csock, "PORT <SP> <host-port> <CRLF>  : \
    Enable 'active' mode for data transfer\n");
    dprintf(csock, "HELP [<SP> <string>] <CRLF>   : \
    List available commands\n");
    dprintf(csock, "NOOP <CRLF>                   : Do nothing\n");
    dprintf(csock, "(the following are commands using data transfer )\n");
    dprintf(csock, "RETR <SP> <pathname> <CRLF>   : \
    Download file from server to client\n");
    dprintf(csock, "STOR <SP> <pathname> <CRLF>   : \
    Upload file from client to server\n");
    dprintf(csock, "LIST [<SP> <pathname>] <CRLF> : \
    List files in the current working directory\n");
}

void help(t_infos *infos, char **cmd)
{
    (void) cmd;
    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    dprintf(infos->csock, "USER <SP> <username> <CRLF>   : \
    Specify user for authentication\n");
    dprintf(infos->csock, "PASS <SP> <password> <CRLF>   : \
    Specify password for authentication\n");
    dprintf(infos->csock, "CWD  <SP> <pathname> <CRLF>   : \
    Change working directory\n");
    dprintf(infos->csock, "CDUP <CRLF>                   : \
    Change working directory to parent directory\n");
    dprintf(infos->csock, "QUIT <CRLF>                   : \
    Disconnection\n");
    dprintf(infos->csock, "DELE <SP> <pathname> <CRLF>   : \
    Delete file on the server\n");
    help_two(infos->csock);
}