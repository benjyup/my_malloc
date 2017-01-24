##
## Makefile for c in /home/puente_t/rendu/PISC_CPP/cpp_d01
## 
## Made by Timothee Puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Wed Jan  4 07:16:58 2017 Timothee Puentes
Last update Tue Jan 24 14:46:58 2017 puente_t
##

NAME		=	libmy_malloc.so

SRCS		=	malloc.c

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc

RM		=	rm -f

CFLAGS		+=	-g -Wall -Werror -Wextra -fpic

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -shared -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all


.PHONY: all clean fclean re
