/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:50:35 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/01/30 19:50:35 by frdal-sa         ###   ########.fr       */
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
	general->path = NULL;
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

void	start_the_work(t_general general)
{
	t_lex		*tmp;

	parser(&general);
	tmp = general.lexer;
	expander(&general);
	executor(&general);
	free_lex(general.lexer);
	general.lexer = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_general	general;

	if (!check_input_number(ac))
		return (0);
	init(&general, envp);
	while (1)
	{
		printf(YELLOW);
		general.args = readline("kitty shell> " RESET);
		if (general.args == NULL)
		{
			ft_printf("sono uscito nel controllo general.args == NULL\n");
			free_and_exit(1, &general);
		}
		if (general.args && *general.args)
			add_history(general.args);
		if (!is_whitespace_input(general.args))
			start_the_work(general);
	}
}
