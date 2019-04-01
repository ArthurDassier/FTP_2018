/*
** EPITECH PROJECT, 2019
** server.c
** File description:
** server
*/

#include "server.h"

SOCKADDR_IN init_sock_addr(int port)
{
    SOCKADDR_IN     sin;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    return (sin);
}

SOCKET init_socket(int port)
{
    SOCKADDR_IN     sin;
    socklen_t       recsize = sizeof(sin);
    SOCKET          sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("Error on socket");
        return (84);
    }
    sin = init_sock_addr(port);
    if (bind(sock, (SOCKADDR*)&sin, recsize) == -1) {
        perror("Error on bind");
        return (84);
    }
    if (listen(sock, 5) == -1) {
        perror("Error on listen");
        return (84);
    }
    return (sock);
}

int main(void)
{
    SOCKADDR_IN     csin;
    SOCKET          csock;
    socklen_t       crecsize = sizeof(csin);
    SOCKET          sock = init_socket(PORT);
    char            *tmp = malloc(sizeof(char) * 14);

    if (sock == 84)
        return (84);
    while (42) {
        csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
        write(csock, "Hello World!\n", 13);
        read(csock, tmp, 13);
        printf("%s", tmp);
    }
    close(csock);
    close(sock);
    return (0);
}