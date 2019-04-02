/*
** EPITECH PROJECT, 2019
** server.h
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

#define CMD_LEN 3

SOCKADDR_IN init_sock_addr(int);
SOCKET init_socket(int);

typedef struct s_cmd
{
    char *cmd;
    void (*pointer)(SOCKET, char **);
}              t_cmd;

typedef struct s_reply
{
    int code;
    char *reply;
}              t_reply;

void send_reply(SOCKET, int);
char **my_str_to_wordtab(char *);

// Utils
int error_handling(int, char **);

// Commands
void help(SOCKET, char **);
void user(SOCKET, char **);
void password(SOCKET, char **);

#endif /* !SERVER_H_ */
