/*
** EPITECH PROJECT, 2019
** lol
** File description:
** lol
*/

#include "server.h"

int main(void)
{
    int sock_err;

    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t recsize = sizeof(sin);
    
    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t crecsize = sizeof(csin);

    pid_t   child_pid;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock != -1) {
        printf("socket accepted\n");
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        sock_err = bind(sock, (SOCKADDR*)&sin, recsize);
        sock_err = listen(sock, 5);

        while (42) {
            csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
            write(csock, "Hello World!\n", 13);
            char *tmp = malloc(sizeof(char) * 14);
            read(csock, tmp, 13);
            printf("%s", tmp);
        }
    }
    close(csock);
    close(sock);
    return (0);
}