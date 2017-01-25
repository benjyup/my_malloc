##
## Makefile for  in /home/puente_t/rendu/PSU_2016_malloc/lib
## 
## Made by timothee.puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Wed Jan 25 15:01:26 2017 timothee.puentes
## Last update Wed Jan 25 15:01:28 2017 timothee.puentes
##

NAME		=	libmy_malloc.so

SRCS		=	malloc.c realloc.c

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
