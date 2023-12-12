/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/12 15:16:48 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int is_whitespace_input(const char *str)
{
    while (*str)
	{
        if (iswhite(*str))
            return 0;
        str++;
    }
    return (1);
}

void	init(t_general *general, char **envp)
{
	general->lexer = NULL;
	general->envp2 = matrix_dup(envp);
	general->path = ft_split(getenv("PATH"), ':');
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
		general.args = readline("kitty shell>");
		if (general.args && *general.args)
			add_history(general.args);
		if (!is_whitespace_input(general.args))
		{
			parser(&general);
			// tmp = general.lexer;

			// //differenziare comandi builtin fra quelli di sistema
			// if (tmp->builtin == 0) {
			// 	execute_external_command(tmp->command2);
			// 	wait(NULL);
			// } else {
			// 	//executebuiltin(tmp->built...)
			// }


			// //debug info
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
		//free memory
		executor(&general);
		afalcons(general.lexer);
		general.lexer = NULL;
		}
	}
}
