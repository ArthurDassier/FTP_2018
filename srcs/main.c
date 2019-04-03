/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "server.h"

static int print_help()
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory \
    for the Anonymous user\n");
    return (1);
}

static int print_help_error()
{
    fprintf(stderr, "USAGE: ./myftp port path\n");
    fprintf(stderr, "\tport is the port number on which the server \
    socket listens\n");
    fprintf(stderr, "\tpath is the path to the home directory \
    for the Anonymous user\n");
    return (84);
}

static int error_handling(int ac, char **av)
{
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0)
            return (print_help());
        else
            return (print_help_error());
    }
    if (ac != 3)
        return (print_help_error());
    for (size_t i = 0; i != strlen(av[1]); ++i) {
        if (!isdigit(av[1][i])) {
            fprintf(stderr, "%s: is not a correct port\n", av[1]);
            return (84);
        }
    }
    if (chdir(av[2]) == -1) {
        fprintf(stderr, "%s: is not a correct path\n", av[2]);
        return (84);
    }
    return (0);
}

int main(int ac, char **av)
{
    int err = error_handling(ac, av);

    if (err == 84)
        return (84);
    else if (err == 1)
        return (0);
    else
        return (loop(av));
}