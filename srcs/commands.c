/*
** EPITECH PROJECT, 2019
** commands.c
** File description:
** commands
*/

#include "server.h"

static cmd_t cmd_table[] =
{
    {"HELP", &help},
    {"USER", &user},
    {"PASS", &password},
    {"NOOP", &noop},
    {"PWD", &pwd},
    {"CDUP", &cdup},
    {"CWD", &cwd},
    {"PASV", &pasv},
    {"STOR", &stor},
    {"LIST", &list},
    {"RETR", &retr},
    {"DELE", &dele},
    {"PORT", &port}
};

void noop(infos_t *infos, char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else
        send_reply(infos->csock, 200);
}

void pwd(infos_t *infos, char **cmd)
{
    char *tmp = NULL;

    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else
        dprintf(infos->csock, "257 \"%s\"\r\n", getcwd(tmp, 200));
}

void cdup(infos_t *infos, char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] != NULL)
        send_reply(infos->csock, 504);
    else {
        if (chdir("..") == -1)
            send_reply(infos->csock, 550);
        else
            send_reply(infos->csock, 200);
    }
}

void cwd(infos_t *infos, char **cmd)
{
    if (infos->user == NOT_LOGGED || infos->pwd == false)
        send_reply(infos->csock, 530);
    else if (cmd[1] == NULL || cmd[2] != NULL)
        send_reply(infos->csock, 504);
    else {
        if (chdir(cmd[1]) == -1)
            send_reply(infos->csock, 550);
        else
            send_reply(infos->csock, 200);
    }
}

int analyse_and_exec_command(infos_t **list, infos_t *infos,
char **tab_cmd, fd_set *active_fd_set)
{
    unsigned int    i = 0;

    for (i = 0; i < ARRAY_SIZE(cmd_table); ++i) {
        if (strncasecmp(tab_cmd[0], cmd_table[i].cmd, 4) == 0) {
            cmd_table[i].pointer(infos, tab_cmd);
            break;
        }
    }
    if (strncasecmp(tab_cmd[0], "QUIT", 4) == 0) {
        if (delete_node(list, infos, active_fd_set) == 84)
            return (84);
        return (0);
    } else if (i == ARRAY_SIZE(cmd_table)) {
        if (infos->pwd == true)
            send_reply(infos->csock, 500);
        else
            send_reply(infos->csock, 530);
    }
    return (0);
}