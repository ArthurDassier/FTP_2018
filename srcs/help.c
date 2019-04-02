/*
** EPITECH PROJECT, 2019
** help.c
** File description:
** help
*/

#include "server.h"

static void help_two(SOCKET csock)
{
    dprintf(csock, "PASV <CRLF>                   : \
    Enable 'passive' mode for data transfer\n");
    dprintf(csock, "PORT <SP> <host-port> <CRLF>  : \
    Enable 'active' mode for data transfer\n");
    dprintf(csock, "HELP [<SP> <string>] <CRLF>   : \
    List available commands\n");
    dprintf(csock, "NOOP <CRLF>                   : \
    Do nothing\n");
    dprintf(csock, "(the following are commands using data transfer )\n");
    dprintf(csock, "RETR <SP> <pathname> <CRLF>   : \
    Download file from server to client\n");
    dprintf(csock, "STOR <SP> <pathname> <CRLF>   : \
    Upload file from client to server\n");
    dprintf(csock, "LIST [<SP> <pathname>] <CRLF> : \
    List files in the current working directory\n");
}

void help(SOCKET csock, char **cmd)
{
    (void) cmd;
    dprintf(csock, "USER <SP> <username> <CRLF>   : \
    Specify user for authentication\n");
    dprintf(csock, "PASS <SP> <password> <CRLF>   : \
    Specify password for authentication\n");
    dprintf(csock, "CWD  <SP> <pathname> <CRLF>   : \
    Change working directory\n");
    dprintf(csock, "CDUP <CRLF>                   : \
    Change working directory to parent directory\n");
    dprintf(csock, "QUIT <CRLF>                   : \
    Disconnection\n");
    dprintf(csock, "DELE <SP> <pathname> <CRLF>   : \
    Delete file on the server\n");
    dprintf(csock, "PWD  <CRLF>                   : \
    Print working directory\n");
    help_two(csock);
}