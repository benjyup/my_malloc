
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
