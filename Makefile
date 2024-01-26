# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 18:22:29 by jcardina          #+#    #+#              #
#    Updated: 2024/01/26 15:23:57 by jcardina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME = minishell
LIBFT = lib/libft/libft.a
PRINTF = lib/ft_printf/libftprintf.a

src = \
		src/mini_shell.c\
		src/ext_command.c\
		src/utils/general_utils.c\
		src/utils/free.c\
		src/parser/parser.c\
		src/parser/lexer_list.c\
		src/parser/lexer_list_utils.c\
		src/parser/path.c\
		src/parser/expander.c\
		src/builtin/pwd.c\
		src/builtin/env.c\
		src/builtin/ft_myexport.c\
		src/builtin/ft_myunset.c\
		src/builtin/cd.c\
		src/builtin/cd_utils.c\
		src/builtin/builtins_utils.c\
		src/builtin/ft_myecho.c\
		src/builtin/ft_myexit.c\
		src/executor/executor.c\

OBJ = $(src:%.c=%.o)

FLAGS = -Wall -Werror -Wextra -g

CC = gcc

all: $(NAME)

$(NAME) : $(OBJ)
	make all bonus -C lib/libft
	make -C lib/ft_printf
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(PRINTF)  -o minishell -lreadline
	@echo "\033[32mmeow compiled\033[0m"
#-lhistory da riaggiungere su linux
clean:
	make clean -C lib/libft
	make clean -C lib/ft_printf
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "\033[33mno sauce\033[0m"

fclean: clean
	make fclean -C lib/libft
	make fclean -C lib/ft_printf
	rm -f $(NAME) $(NAME_BONUS)
	@echo "\033[33m& no name\033[0m"

re: fclean all

.PHONY:		all clean fclean re
