
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 18:23:28 by hel-ouar          #+#    #+#              #
#    Updated: 2023/02/09 13:33:47 by ikaismou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 

SRCS = main.c init_env/init_env.c exec/exec.c utils/error.c builtins/builtins.c \
		utils/find_path.c utils/list.c parsing/check_line.c utils/wait.c parsing/token.c parsing/redirection.c \
		signal/signal.c parsing/parsing_utils.c builtins/cd.c builtins/env.c builtins/pwd.c builtins/export.c builtins/unset.c \
		builtins/exit.c exec/here_doc.c exec/pipe.c exec/simple_exec.c exec/exec_utils.c exec/redir_exec.c\
		parsing/quote.c
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = minishell

HEAD = include/minishell.h

RM = rm -f

%.o: %.c Makefile ${HEAD}
		${CC} ${FLAGS} -ILibft -c $< -o $@ 

all: Libft $(NAME)

$(NAME): $(OBJS) Libft
	$(CC) $(OBJS) Libft/libft.a -o $(NAME) -lreadline

clean:
	${MAKE} clean -C Libft/

Libft :
	${MAKE} -C Libft
	
fclean: clean
	${MAKE} fclean -C Libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)
	
re: fclean
	make all

.PHONY:	all clean fclean re bonus Libft