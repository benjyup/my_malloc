##
## Makefile for  in /home/puente_t/rendu/PSU_2016_malloc/lib
## 
## Made by timothee.puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Fri Jan 27 16:37:49 2017 timothee.puentes
## Last update Thu Feb  9 16:41:19 2017 timothee.puentes
##

NAME		=	libmy_malloc.so

SRCS		=	malloc.c realloc.c realloc_sup.c free.c \
			calloc.c show_malloc.c

OBJS		=	$(SRCS:.c=.o)

CC		=	gcc

RM		=	rm -f

CFLAGS		+=	-Wall -Werror -Wextra -fpic

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -shared -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all


.PHONY: all clean fclean re
