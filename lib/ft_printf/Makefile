# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 15:47:29 by jcardina          #+#    #+#              #
#    Updated: 2023/11/07 18:37:17 by jcardina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME = libftprintf.a

SRCS =	ft_char.c\
		ft_exa.c\
		ft_number.c\
		ft_putptr.c\
		ft_printf.c\

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJECT = ${SRCS:.c=.o}

RM = rm -f

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

all : ${NAME}

$(NAME) : ${OBJECT}
	ar rcs ${NAME} ${OBJECT}

clean :
	${RM} ${OBJECT}

fclean : clean
	${RM} ${NAME}

re : fclean all
