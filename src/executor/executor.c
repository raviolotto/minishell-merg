/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/30 14:15:08 by jcardina         ###   ########.fr       */
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

int	execute_external_command(t_lex *node, t_general *general, int *save_fd)
{
	int	pid;
	int	fd[2];
	int	status;

	if(node->next && node->next->token == 1)
	{
		if (pipe(fd) == -1)
			perror("non é stato possibile creare la pipe");
	}
	pid = fork();
	if (pid == 0)
	{
		if(node->next && node->next->token == 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
		}
		else if (node->next == NULL)
			dup2(save_fd[1], STDOUT_FILENO);
		if (node->builtin > 0)
		{
			builtinmanager(node, general);
			exit(0); //potrebbe essere utile returnare exit status?
		}
		execve(node->command2[0], node->command2, NULL);
			perror("il comando esterno non é stato eseguito\n");
	}
	waitpid(pid, &status, 0);
	if (node->next && node->next->token == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return WIFEXITED(status) && WEXITSTATUS(status);
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
			g_last_exit_status = execute_external_command(tmp, general, save_fd);
		tmp = tmp->next;
	}
	dup2(save_fd[0], STDIN_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}
