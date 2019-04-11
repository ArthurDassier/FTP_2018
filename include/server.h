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
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;
typedef int int_socket;

#define ARRAY_SIZE(array) sizeof(array) / sizeof(*array)

enum user_state
{
    NOT_LOGGED,
    UNKNOW,
    KNOW
};

enum state
{
    NORMAL,
    PASSIVE,
    ACTIVE
};

typedef struct s_infos
{
    int_socket          csock;
    int_socket          psock;
    sockaddr_in_t       csin;
    int                 user;
    bool                pwd;
    char                *home;
    struct s_infos      *next;
    int                 state;
    char                *construct;
    size_t              constru;
}              infos_t;

typedef struct s_help
{
    char *cmd;
    char *msg;
}              help_t;

typedef struct s_cmd
{
    char *cmd;
    void (*pointer)(infos_t *, char **);
}              cmd_t;

typedef struct s_reply
{
    int  code;
    char *reply;
}              reply_t;

// Utils
int add_node(infos_t **, int_socket, sockaddr_in_t, char *);
int delete_node(infos_t **, infos_t *, fd_set *);

// Commands
int analyse_and_exec_command(infos_t **, infos_t *, char **, fd_set *);
void password(infos_t *, char **);
void help(infos_t *, char **);
void user(infos_t *, char **);
void noop(infos_t *, char **);
void cdup(infos_t *, char **);
void pwd(infos_t *, char **);
void cwd(infos_t *, char **);
void pasv(infos_t *, char **);
void stor(infos_t *, char **);
void list(infos_t *, char **);
void retr(infos_t *, char **);
void dele(infos_t *, char **);
void port(infos_t *, char **);

// Miscellaneous
char **my_str_to_wordtab(char *);
void send_reply(int_socket, int);
int_socket init_socket(int);
int loop(char **);

#endif /* !SERVER_H_ */
