# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 18:22:29 by jcardina          #+#    #+#              #
#    Updated: 2024/02/09 22:26:20 by jcardina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME = minishell
LIBFT = lib/libft/libft.a
PRINTF = lib/ft_printf/libftprintf.a

src = \
		src/mini_shell.c\
		src/utils/general_utils.c\
		src/utils/general_utils2.c\
		src/utils/general_utils3.c\
		src/utils/free.c\
		src/parser/parser.c\
		src/parser/lexer_list.c\
		src/parser/lexer_list_utils.c\
		src/parser/path.c\
		src/parser/path_utils.c\
		src/parser/expander.c\
		src/parser/expander_utils.c\
		src/parser/expander_utils2.c\
		src/builtin/pwd.c\
		src/builtin/env.c\
		src/builtin/export.c\
		src/builtin/export_utils.c\
		src/builtin/unset.c\
		src/builtin/cd.c\
		src/builtin/cd_utils.c\
		src/builtin/cd_utils2.c\
		src/builtin/builtins_utils.c\
		src/builtin/echo.c\
		src/builtin/exit.c\
		src/executor/executor.c\
		src/executor/executor_utils.c\
		src/executor/redir_out.c\
		src/executor/redir_in.c\
		src/executor/redir_hd.c\

OBJ = $(src:%.c=%.o)

FLAGS = -Wall -Werror -Wextra -g

CC = gcc

all: $(NAME)

$(NAME) : $(OBJ)
	make all bonus -C lib/libft
	make -C lib/ft_printf
	$(CC) $(OBJ) $(FLAGS) $(LIBFT) $(PRINTF)  -o minishell -lreadline -lhistory -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
	@echo "\033[32mmeow compiled\033[0m"
clean:
	make clean -C lib/libft
	make clean -C lib/ft_printf
	rm -f $(OBJ)
	@echo "\033[33mno sauce\033[0m"

fclean: clean
	make fclean -C lib/libft
	make fclean -C lib/ft_printf
	rm -f $(NAME)
	@echo "\033[33m& no name\033[0m"

re: fclean all

.PHONY:		all clean fclean re
