##
## Makefile for c in /home/puente_t/rendu/PISC_CPP/cpp_d01
## 
## Made by Timothee Puentes
## Login   <puente_t@epitech.net>
## 
## Started on  Wed Jan  4 07:16:58 2017 Timothee Puentes
## Last update Mon Jan 23 21:38:32 2017 Timothee Puentes
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
