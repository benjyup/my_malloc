##
## Makefile for  in /home/puente_t/rendu/PSU_2016_malloc/lib
## 
## Made by timothee.puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Thu Jan 26 13:59:10 2017 timothee.puentes
## Last update Mon Jan 30 12:10:45 2017 timothee.puentes
##

NAME		=	test

SRCS		=	main.c

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc

RM		=	rm -f

LDFLAGS		=	lib/libmy_malloc.so

CFLAGS		+=	-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) -fpic $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all


.PHONY: all clean fclean re
