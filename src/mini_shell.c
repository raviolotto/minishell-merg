/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/11 18:56:36 by frdal-sa         ###   ########.fr       */
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

void init(t_general *general, char **envp)
{
	general->lexer = NULL;
	general->envp2 = matrix_dup(envp);
	general->path = ft_split(getenv("PATH"), ':');
	printf(PINK "\n%s\n", INTRO);
	printf("\n%s\n" RESET, HELLO2);
}

int is_builtin_command(const char *command)
{
	const char *allowed_commands[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	int i;
	int found;

	i = 0;
	found = 0;

	while (i < sizeof(allowed_commands) / sizeof(allowed_commands[0]) && !found)
	{
		if (ft_strncmp(command, allowed_commands[i], ft_strlen(command)) == 0)
		{
			found = 1;
		}
		i++;
	}

	return found;
}

// execute_builtin_command
void execute_builtin_command(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: echo\n");
		// builtin_echo(args);
	}
	else if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: cd\n");
		// builtin_cd(args, general);
	}
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: pwd\n");
		// builtin_pwd();
	}
	else if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: export\n");
		// builtin_export(args, general);
	}
	else if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: unset\n");
		// builtin_unset(args, general);
	}
	else if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: env\n");
		// builtin_env(general);
	}
	else if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
	{
		printf("execute_builtin_command: exit\n");
		// builtin_exit(args);
	}
}

int main(int ac, char **av, char **envp)
{
	t_general general;
	t_lex *tmp;

	if (ac != 1)
	{
		printf(RED "error dumb input\n" RESET);
		return (0);
	}
	init(&general, envp);
	while (1)
	{
		general.args = readline("kitty shell>");
		if (
			// strlen(general.args) > 0 &&
			!is_whitespace_input(general.args))
		{
			parser(&general);
			tmp = general.lexer;

			// check se usare le nostre funzioni o quelle di sistema (da rivedere, command non )
			if (is_builtin_command(tmp->command))
			{
				printf("execute_builtin_command\n");
				execute_builtin_command(tmp->command);
			}
			else
			{
				printf("execute_external_command %s\n", tmp->command);
				execute_external_command(tmp->command2);
				wait(NULL);
			}
			// debug info (da togliere in futuro)
			while (tmp != NULL)
			{
				printf("token %i\n", tmp->token);
				printf("pipe steatus %i\n", tmp->pipe_status);
				printf("command %s\n", tmp->command);
				print_matrix(tmp->command2);
				printf("\n");
				tmp = tmp->next;
			}
			// free momory
			afalcons(general.lexer);
			general.lexer = NULL;
		}
	}
}
