/*
** EPITECH PROJECT, 2019
** client
** File description:
** clecnt
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 1025

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


int main(void)
{
    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t recsize = sizeof(sin);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    connect(sock, (SOCKADDR*)&sin, sizeof(sin));
    char *tmp = malloc(sizeof(char) * 14);
    read(sock, tmp, 13);
    write(sock, "Hello!\n", 7);
    printf("%s", tmp);
    close(sock);
    return (0);
}