/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/14 19:06:15 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	g_last_exit_status;

void	init(t_general *general, char **environment_variables)
{
	general->lexer = NULL;
	general->environment_variables = matrix_dup(environment_variables);
	general->expanded_environment = matrix_dup(general->environment_variables);
	general->path = NULL;
	general->save_exit_status = 0;
	printf(PINK"\n%s\n", INTRO);
	printf("\n%s\n"RESET, HELLO2);
}

void	handle_sigint(int sig)
{
	//rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("\n");
	rl_redisplay();
	g_last_exit_status = 130;
}

void	handle_sigquit(int sig)
{
	g_last_exit_status = 0;
}

void	core(t_general *general)
{
	parser(general);
	expander(general);
	executor(general);
	free_lex(general->lexer);
	general->lexer = NULL;
}

int	main(int ac, char **av, char **environment_variables)
{
	t_general	general;
	t_lex		*tmp;

	if (ac != 1)
		return (printf(RED "Error dumb input\n" RESET), 0);
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	init(&general, environment_variables);

	while (1)
	{
		g_last_exit_status = 0;
		general.user_input = readline(YELLOW "kitty shell> " RESET);
		printf("user_input: %s\n", general.user_input);
		if (general.user_input == NULL)
		{
			ft_printf("exit\n");
			free_and_exit(general.save_exit_status, &general);
		}
		if (general.user_input && *general.user_input)
			add_history(general.user_input);
		if (!is_whitespace_input(general.user_input))
			core(&general);
	}
}
