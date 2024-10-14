# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 00:25:27 by youssra           #+#    #+#              #
#    Updated: 2024/10/13 23:43:11 by kaafkhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
CC			=	cc

CFLAGS		=	-g -Wall -Wextra -Werror -I./ -I./lib/Libft -I$(shell brew --prefix readline)/include
LIBS 		= -L$(shell brew --prefix readline)/lib -lreadline

HEADER		=	minishell.h

LIBRARY		=	lib/libft.a

SRCS		=	parse/main.c \
				parse/tools/before_parse.c \
				parse/tools/error.c \
				parse/tools/freeing.c \
				parse/tools/expand.c \
				parse/tools/heredoc.c \
				parse/tools/tokenizer_tools.c \
				parse/lexical_analyzer/create_tokens.c \
				parse/lexical_analyzer/parser.c \
				parse/lexical_analyzer/parsing_process.c \
				exec/exec_cmd.c \
				exec/tools.c \
				exec/process_cmds.c \
				exec/builtins.c \
				exec/builtins2.c \
				exec/exuc_built.c \
				exec/signals.c

OBJS		= $(SRCS:.c=.o)

all : $(NAME)

lib :
	make -C lib

$(NAME): $(OBJS) lib
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) -o $(NAME) $(LIBS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib
	rm -rf $(OBJS)

fclean:	clean
	make fclean -C lib
	rm -rf $(NAME)

re: fclean all

push: fclean
	git add .
	git commit -m "parse"
	git push

.PHONY: clean fclean re lib
