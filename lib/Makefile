

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
