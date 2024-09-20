NAME 		=	minishell
CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror

LFLAGS 		=	-L$(shell brew --prefix readline)/libf -lreadline

HEADER		=	minishell.h

LIBRARY		=	libf/libft.a

SRCS		=	builtins.c main.c exuc_built.c freeing.c

OBJS		= $(SRCS:.c=.o)

all : $(NAME)

lib :
	@echo "makaynach libf directory "

$(NAME) : $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME) $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "parse"
	git push

.PHONY: clean fclean re lib
