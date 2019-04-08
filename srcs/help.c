/*
** EPITECH PROJECT, 2019
** help.c
** File description:
** help
*/

#include "server.h"

static help_t help_table[] =
{
    {"HELP", "List available commands"},
    {"USER", "Specify user for authentication"},
    {"PASS", "Specify password for authentication"},
    {"NOOP", "Do nothing"},
    {"PWD", "Print working directory"},
    {"CDUP", "Change working directory to parent directory"},
    {"CWD", "Change working directory to parent directory"},
    {"PASV", "Enable \"passive\" mode for data transfer"},
    {"QUIT", "Disconnection"},
    {"PORT", "Enable \"active\" mode for data transfer"},
    {"RETR", "Download file from server to client"},
    {"STOR", "Upload file from client to server"},
    {"LIST", "List files in the current working directory"},
    {"DELE", "Delete file on the server"}
};

static void help_two(infos_t *infos, char **cmd)
{
    dprintf(infos->csock, "214 ");
    for (unsigned int i = 0; i < ARRAY_SIZE(help_table); ++i) {
        if (strncasecmp(cmd[1], help_table[i].cmd, 4) == 0) {
            dprintf(infos->csock, "%s : %s.\r\n", help_table[i].cmd,
                        help_table[i].msg);
            break;
        }
    }
}

void help(infos_t *infos, char **cmd)
{
    unsigned int i = 0;

    if (infos->user == NOT_LOGGED || infos->pwd == false) {
        send_reply(infos->csock, 530);
        return;
    }
    if (cmd[1] == NULL) {
        dprintf(infos->csock, "214 ");
        for (i = 0; i < ARRAY_SIZE(help_table) - 1; ++i)
            dprintf(infos->csock, "%s : %s.\n", help_table[i].cmd,
                    help_table[i].msg);
        dprintf(infos->csock, "%s : %s.\r\n", help_table[i].cmd,
                help_table[i].msg);
        return;
    } else if (cmd[2] != NULL)
        send_reply(infos->csock, 504);
    else
        help_two(infos, cmd);
}