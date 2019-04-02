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
    {"PASS", &password}
};

int found_cmd(char *tmp, SOCKET sock, SOCKET csock)
{
    (void)  sock;
    size_t  i = 0;
    int     size = 0;
    char    **cmd;

    while ((size = read(csock, tmp, 2000))) {
        if (size == -1)
            exit(0);
        tmp[size - 1] = '\0';
        cmd = my_str_to_wordtab(tmp);
        for (; i < CMD_LEN; ++i) {
            if (strcmp(cmd[0], cmd_table[i].cmd) == 0) {
                cmd_table[i].pointer(csock, cmd);
                break;
            }
        }
        if (strcmp(tmp, "QUIT") == 0) {
            free(cmd);
            free(tmp);
            close(csock);
            return (1);
        } else if (i == CMD_LEN)
            send_reply(csock, 500);
        for (size_t i = 0; i < 2000; ++i)
            tmp[i] = '\0';
        free (cmd);
    }
    return (0);
}

int loop(int port)
{
    SOCKADDR_IN     csin;
    SOCKET          csock;
    socklen_t       crecsize = sizeof(csin);
    SOCKET          sock = init_socket(port);
    char            *tmp = malloc(sizeof(char) * 2000);

    if (sock == 84)
        return (84);
    while (42) {
        csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
        if (csock == -1)
            break;
        if (fork() == 0) {
            send_reply(csock, 220);
            found_cmd(tmp, sock, csock);
            return (0);
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    int err = error_handling(ac, av);

    if (err == 84)
        return (84);
    else if (err)
        return (0);
    else
        return (loop(atoi(av[1])));
}