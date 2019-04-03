/*
** EPITECH PROJECT, 2019
** server.c
** File description:
** server
*/

#include "server.h"

t_cmd cmd_table[CMD_LEN] =
{
    {"HELP", &help},
    {"USER", &user},
    {"PASS", &password},
    {"NOOP", &noop},
    {"PWD", &pwd},
    {"CDUP", &cdup},
    {"CWD", &cwd}
};

int exec_command(t_infos *infos)
{
    char    **tab_cmd = NULL;
    int     size = 0;
    int     i = 0;
    char    *command = malloc(sizeof(char) * 2000);

    if (infos == NULL || command == NULL)
        return (84);
    size = read(infos->csock, command, 2000);
    if (size == -1)
        return (84);
    command[size - 1] = '\0';
    tab_cmd = my_str_to_wordtab(command);
    for (i = 0; i < CMD_LEN; ++i) {
        if (strcmp(tab_cmd[0], cmd_table[i].cmd) == 0) {
            cmd_table[i].pointer(infos, tab_cmd);
            break;
        }
    }
    if (i == CMD_LEN)
        send_reply(infos->csock, 500);
    free(tab_cmd);
    return (0);
}

static int check_fd_is_set(t_infos **infos, fd_set read_fd_set)
{
    t_infos *infos_tmp = (*infos);

    while (infos_tmp != NULL && !(FD_ISSET(infos_tmp->csock, &read_fd_set)))
        infos_tmp = infos_tmp->next;
    if (infos_tmp != NULL)
        exec_command(infos_tmp);
    return (0);
}

static int new_connection(SOCKET sock, t_infos **infos,
fd_set *fdst, char *path)
{
    SOCKET          csock;
    SOCKADDR_IN     csin;
    socklen_t       crecsize = sizeof(csin);

    csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
    send_reply(csock, 220);
    FD_SET(csock, fdst);
    if (add_node(infos, csock, path) == 84)
        return (84);
    return (0);
}

static int select_management(SOCKET sock, t_infos **infos,
fd_set *active_fd_set, char *path)
{
    fd_set read_fd_set = *active_fd_set;

    if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) == -1) {
        perror("Error on select");
        return (84);
    }
    if (FD_ISSET(sock, &read_fd_set)) {
        if (new_connection(sock, infos, active_fd_set, path) == 84)
            return (84);
    }
    if (check_fd_is_set(infos, read_fd_set) == 84)
        return (84);
    return (0);
}

int loop(char **av)
{
    SOCKET     sock = init_socket(atoi(av[1]));
    fd_set     active_fd_set;
    t_infos    *infos = NULL;

    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);
    if (sock == 84)
        return (84);
    while (42) {
        if (select_management(sock, &infos, &active_fd_set, av[2]) == 84)
            return (84);
    }
    return (0);
}
