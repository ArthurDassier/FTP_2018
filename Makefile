##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## a_makefile_for_projetcs
##

CC		=	gcc -g3

RM		=	rm -rf

CFLAGS	+=	-Wall -Wextra

CFLAGS	+=	-I./include

NAME	=	myftp

SRCS	=	srcs/main.c					\
			srcs/utils.c				\
			srcs/server.c				\
			srcs/help.c					\
			srcs/passive.c				\
			srcs/commands.c				\
			srcs/init.c					\
			srcs/reply.c				\
			srcs/user.c					\
			srcs/my_str_to_wordtab.c	\

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
