/*
** EPITECH PROJECT, 2019
** reply.c
** File description:
** reply
*/

#include "server.h"

t_reply replies_tab[22] =
{
    {550, "File or directory doesn't exist.\n"},
    {530, "Please login with USER and PASS.\n"},
    {504, "Command not implemented for that parameter.\n"},
    {503, "Login with USER first.\n"},
    {500, "Unknown command.\n"},
    {120, "Service ready in x minutes.\n"},
    {451, "Requested action aborted. Local error in processing.\n"},
    {430, "Invalid username or password.\n"},
    {425, "Use PORT or PASV first.\n"},
    {332, "Need account for login.\n"},
    {331, "User name okay, need password.\n"},
    {257, "\"PATHNAME\" created.\n"},
    {250, "Requested file action okay, completed.\n"},
    {230, "User logged in, proceed.\n"},
    {227, "Entering Passive Mod ("},
    {226, "Closing data connection.\n"},
    {221, "Service closing control connection.\n"},
    {220, "Service ready for new user.\n"},
    {214, "Help message.\n"},
    {200, "Command okay.\n"},
    {150, "File status okay; about to open data connection.\n"},
    {125, "Data connection already open; transfer starting.\n"}
};

void send_reply(SOCKET csock, int code)
{
    for (int i = 0; i != 22; ++i) {
        if (code == replies_tab[i].code) {
            dprintf(csock, "%d %s\n", replies_tab[i].code,
            replies_tab[i].reply);
        }
    }
}