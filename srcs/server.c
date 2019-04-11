/*
** EPITECH PROJECT, 2019
** server.c
** File description:
** server
*/

#include <signal.h>
#include "server.h"

int format_command(infos_t **list, infos_t *infos, fd_set *active_fd_set)
{
    char    **tab_cmd = NULL;
    char    command[4096];
    int     size = 0;

    if (infos == NULL || command == NULL)
        return (84);
    size = read(infos->csock, command, 4096);
    if (size == -1)
        return (84);
    if (size < 3 || strcmp(command, "\r\n") == 0 || strcmp(command, "\r") == 0
    || strcmp(command, "\n") == 0)
        return (0);
    command[size] = '\0';
    tab_cmd = my_str_to_wordtab(command);
    if (analyse_and_exec_command(list, infos, tab_cmd, active_fd_set) == 84)
        return (84);
    for (size_t i = 0; i < 4096; ++i)
        command[i] = '\0';
    free(tab_cmd);
    return (0);
}

static int check_fd_is_set(infos_t **infos,
fd_set *active_fd_set, fd_set read_fd_set)
{
    infos_t *infos_tmp = (*infos);

    while (infos_tmp != NULL && !(FD_ISSET(infos_tmp->csock, &read_fd_set)))
        infos_tmp = infos_tmp->next;
    if (infos_tmp != NULL)
        format_command(infos, infos_tmp, active_fd_set);
    return (0);
}

static int new_connection(int_socket sock, infos_t **infos,
fd_set *fdst, char *path)
{
    int_socket          csock;
    sockaddr_in_t     csin;
    socklen_t       crecsize = sizeof(csin);

    csock = accept(sock, (sockaddr_t*)&csin, &crecsize);
    send_reply(csock, 220);
    FD_SET(csock, fdst);
    if (add_node(infos, csock, csin, path) == 84)
        return (84);
    return (0);
}

static int select_management(int_socket sock, infos_t **infos,
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
    if (check_fd_is_set(infos, active_fd_set, read_fd_set) == 84)
        return (84);
    return (0);
}

int loop(char **av)
{
    int_socket     sock = init_socket(atoi(av[1]));
    fd_set     active_fd_set;
    infos_t    *infos = NULL;

    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);
    if (sock == 84)
        return (84);
    while (42) {
        if (select_management(sock, &infos, &active_fd_set, av[2]) == 84) {
            close(sock);
            return (84);
        }
    }
    close(sock);
    return (0);
}
