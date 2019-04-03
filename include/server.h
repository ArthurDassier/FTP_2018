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
#include <stdbool.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

#define CMD_LEN 7

SOCKADDR_IN init_sock_addr(int);
SOCKET init_socket(int);

enum user_state
{
    NOT_LOGGED,
    UNKNOW,
    KNOW
};

typedef struct s_infos
{
    SOCKET     csock;
    int        user;
    bool       pwd;
    char       *home;
}              t_infos;

typedef struct s_cmd
{
    char *cmd;
    void (*pointer)(t_infos *, char **);
}              t_cmd;

typedef struct s_reply
{
    int  code;
    char *reply;
}              t_reply;

t_infos *init_struct(SOCKET, char *);
void send_reply(SOCKET, int);
char **my_str_to_wordtab(char *);

// Utils
int error_handling(int, char **);

// Commands
void help(t_infos *, char **);
void user(t_infos *, char **);
void password(t_infos *, char **);
void noop(t_infos *, char **);
void pwd(t_infos *, char **);
void cdup(t_infos *, char **);
void cwd(t_infos *, char **);

#endif /* !SERVER_H_ */
