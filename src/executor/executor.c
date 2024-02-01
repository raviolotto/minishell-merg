/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/01 18:13:21 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	re_out(t_lex *node, t_general *general, int *save_fd)
{
	int	file;

	write(1, "a\n", 2);
	if (node->next->token == 2)
		file = open(node->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (node->next->token == 3)
		file = open(node->next->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
		return (1);
	dup2(file, STDOUT_FILENO);
	close(file);
	if (node->builtin > 0)
	{
		builtinmanager(node, general);
		dup2(save_fd[1], STDOUT_FILENO);
		exit (g_last_exit_status); //potrebbe essere utile returnare exit status?
	}
	execve(node->command2[0], node->command2, NULL);
}

int	piping(int *fd, int *save_fd, t_lex *node, t_general *general)
{
	if(node->next && node->next->token == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	else if (node->next == NULL)
		dup2(save_fd[1], STDOUT_FILENO);
	if (node->builtin == 1 || node->builtin == 3 || node->builtin == 6)
	{
		builtinmanager(node, general);
		exit (g_last_exit_status); //potrebbe essere utile returnare exit status?
	}
	execve(node->command2[0], node->command2, NULL);
	perror("il comando esterno non é stato eseguito\n");
}

int	pid_manager(int *fd, int *save_fd, t_lex *node, t_general *general)
{
	int	pid;

	pid = fork();

	if (pid == 0)
	{
		if (node->next == NULL || node->next->token == 1)
		{
			write(1, "v\n", 2);
			piping(fd, save_fd, node, general);
		}
		else if (node->next->token == 2 || node->next->token == 3)
		{
			write(1, "b\n", 2);
			re_out(node, general);
		}
		else
			write(1, "p\n", 2);
	}
	return (pid);
}


int	execute_command(t_lex *node, t_general *general, int *save_fd)
{
	int	pid;
	int	fd[2];
	//int	status;

	if (node->builtin != 1 && node->builtin != 3 
		&& node->builtin != 6 && node->builtin != 0)
	{
		builtinmanager(node, general);
		return (g_last_exit_status);
	}
	if (node->next && node->next->token == 1)
	{
		if (pipe(fd) == -1)
			perror("non é stato possibile creare la pipe");
	}
	pid = fork();
	if (pid == 0)
	{
			if(node->next == NULL || node->next->token == 1)
				piping(fd, save_fd, node, general);
			else if(node->next->token == 2 || node->next->token == 3)
				re_out(node, general, save_fd);
			else
				write(1, "p\n", 2);
	}
	//waitpid(pid, &status, 0);
	wait(NULL);
	if (node->next && node->next->token == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	//return WIFEXITED(status) && WEXITSTATUS(status);
	return(0);
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
		if (tmp->token == 0)
			g_last_exit_status = execute_command(tmp, general, save_fd);
		tmp = tmp->next;
	}
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}
