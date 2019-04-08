/*
** EPITECH PROJECT, 2019
** reply.c
** File description:
** reply
*/

#include "server.h"

static reply_t replies_tab[] =
{
    {550, "File or directory doesn't exist.\r\n"},
    {530, "Please login with USER and PASS.\r\n"},
    {504, "Command not implemented for that parameter.\r\n"},
    {503, "Login with USER first.\r\n"},
    {500, "Unknown command.\r\n"},
    {120, "Service ready in x minutes.\r\n"},
    {451, "Requested action aborted. Local error in processing.\r\n"},
    {430, "Invalid username or password.\r\n"},
    {425, "Use PORT or PASV first.\r\n"},
    {332, "Need account for login.\r\n"},
    {331, "User name okay, need password.\r\n"},
    {257, "\"PATHNAME\" created.\r\n"},
    {250, "Requested file action okay, completed.\r\n"},
    {230, "User logged in, proceed.\r\n"},
    {227, "Entering Passive Mod ("},
    {226, "Closing data connection.\r\n"},
    {221, "Service closing control connection.\r\n"},
    {220, "Service ready for new user.\r\n"},
    {214, "Help message.\r\n"},
    {200, "Command okay.\r\n"},
    {150, "File status okay; about to open data connection.\r\n"},
    {125, "Data connection already open; transfer starting.\r\n"}
};

void send_reply(SOCKET csock, int code)
{
    for (int i = 0; i != ARRAY_SIZE(replies_tab); ++i) {
        if (code == replies_tab[i].code) {
            dprintf(csock, "%d %s", replies_tab[i].code,
            replies_tab[i].reply);
        }
    }
}