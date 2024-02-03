/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/03 20:57:42 by lmorelli         ###   ########.fr       */
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
	general->lexer = NULL;
	general->envp2 = matrix_dup(envp);
	general->enexp = matrix_dup(general->envp2);
	general->path = NULL;
	general->save_exit_status = 0;
	printf(PINK"\n%s\n", INTRO);
	printf("\n%s\n"RESET, HELLO2);
}

void	handle_sigint(int sig)
{
	//free(general->args);
	ft_printf(YELLOW"\nkitty shell>" RESET);
	g_last_exit_status = 130;
}

void	handle_sigquit(int sig)
{
	g_last_exit_status = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_general	general;
	t_lex		*tmp;

	if (ac != 1)
	{
		printf(RED "error dumb input\n" RESET);
		return (0);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	init(&general, envp);
	while (1)
	{
		g_last_exit_status = 0;
		printf(YELLOW);
		general.args = readline("kitty shell> " RESET);
		if (general.args == NULL)
		{
			ft_printf("exit\n");
			free_and_exit(general.save_exit_status, &general);
		}
		if (general.args && *general.args)
			add_history(general.args);
		if (!is_whitespace_input(general.args))
		{
		// if(g_last_exit_status == 130)
		// {
		// 	ft_printf("aaaaaaaaaaaaaaaa\n");
		// 	free(general.args);
		// }
			parser(&general);
			expander(&general);
			//                       debug info
			// tmp = general.lexer;
			// ft_printf(RED);
			// while (tmp != NULL)
			// {
			// 	printf("token %i\n", tmp->token);
			// 	printf("pipe steatus %i\n", tmp->pipe_status);
			// 	printf("command %s\n", tmp->command);
			// 	printf("builtin == %i\n", tmp->builtin);
			// 	print_matrix(tmp->command2);
			// 	printf("questo é index == %d\n", tmp->i);
			// 	printf("\n");
			// 	tmp = tmp->next;
			// }
			// ft_printf("fine scroll\n");
			// ft_printf("giusta redir == %d\n", find_correct_redir(&general));
			// ft_printf(RESET);
			//                      end debug info;
			executor(&general);
			free_lex(general.lexer);
			general.lexer = NULL;
		}
	}
}
