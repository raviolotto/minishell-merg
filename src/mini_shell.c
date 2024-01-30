/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/30 14:02:44 by jcardina         ###   ########.fr       */
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
	//general->path = ft_split(getenv("PATH"), ':');
	printf(PINK"\n%s\n", INTRO);
	printf("\n%s\n"RESET, HELLO2);
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
		//ricordati di freeeeeare
		if (general.args && *general.args)
			add_history(general.args);
		if (!is_whitespace_input(general.args))
		{
			parser(&general);
			tmp = general.lexer;
			//debug info
			// printf(RED);
			// while (tmp != NULL)
			// {
			// 	printf("token %i\n", tmp->token);
			// 	printf("pipe steatus %i\n", tmp->pipe_status);
			// 	printf("command %s\n", tmp->command);
			// 	printf("builtin == %i\n", tmp->builtin);
			// 	print_matrix(tmp->command2);
			// 	printf("\n");
			// 	tmp = tmp->next;
			// }
			// printf(RESET);

		//	print_matrix(general.lexer->command2);
	//gestionene $
			expander(&general);
			//print_matrix(general.lexer->command2);
			executor(&general);
			//free memory
			free_lex(general.lexer);
			general.lexer = NULL;
		}
	}
}
