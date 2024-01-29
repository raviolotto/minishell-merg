/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/29 18:26:34 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	builtinmanager(t_lex *node, t_general *general)
{
	if (node->builtin == 1)
		handle_echo(general, node);
	if (node->builtin == 2)
		handle_cd(general, node);
	if (node->builtin == 3)
		handle_pwd();
	if (node->builtin == 4)
		handle_export(general, node);
	if (node->builtin == 5)
		handle_unset(general, node);
	if (node->builtin == 6)
		handle_env(general);
	if (node->builtin == 7)
		handle_exit(node->command2, general);
}

int	execute_external_command(t_lex *node, t_general *general)
{
	int	pid;
	int	fd[2];

	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if(node->next && node->next->token == 1)
	{
		if (pipe(fd) == -1)
			perror("non é stato possibile creare la pipe");
	}
	if (pid1 == 0)
	{
		if (node->builtin > 0)
		{
			builtinmanager(node, general);
			return (0); //potrebbe essere utile returnare exit status?
		}
		if(node->next && node->next->token == 1)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		execve(node->command2[0], node->command2, NULL);
	}
	waitpid(pid1, NULL, 0);
	if(node->next && node->next->token == 1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
void	executor(t_general *general)
{
	t_lex	*tmp;
	int		save_fd[2];

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	tmp = general->lexer;
	while (tmp)
	{
		if(tmp->token != 1)
			execute_external_command(tmp, general);
		wait(NULL);
		tmp = tmp->next;
	}
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}
