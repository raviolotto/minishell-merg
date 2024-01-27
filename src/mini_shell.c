/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/27 15:37:11 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	g_last_exit_status;

static int	is_whitespace_input(const char *str)
{
	while (*str)
	{
		if (iswhite(*str))
			return (0);
		str++;
	}
	return (1);
}

void	init(t_general *general, char **envp)
{
	g_last_exit_status = 0;
	general->lexer = NULL;
	general->envp2 = matrix_dup(envp);
	general->enexp = matrix_dup(general->envp2);
	general->path = ft_split(getenv("PATH"), ':');
	printf(PINK"\n%s\n", INTRO);
	printf("\n%s\n"RESET, HELLO2);
}

int	check_input_number(int ac)
{
	if (ac != 1)
	{
		printf(RED "error dumb input\n" RESET);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_general	general;
	t_lex		*tmp;

	if (!check_input_number(ac))
		return (0);
	init(&general, envp);
	while (1)
	{
		printf(YELLOW);
		general.args = readline("kitty shell> " RESET);
		if (general.args == NULL)
			exit(1);
		if (general.args && *general.args)
			add_history(general.args);
		if (!is_whitespace_input(general.args))
		{
			parser(&general);
			tmp = general.lexer;
			expander(&general);
			executor(&general);
			afalcons(general.lexer);
			general.lexer = NULL;
		}
	}
}
