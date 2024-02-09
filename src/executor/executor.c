/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/09 22:29:31 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	piping(int *fd, int *save_fd, t_lex *node, t_general *general)
{
	if (node->next && node->next->token == 1)
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
		exit (g_last_exit_status);
	}
	execve(node->command2[0], node->command2, NULL);
	perror("execve: Command not found\n");
}

void	execute_command2(t_lex *node, t_general *general, int *save_fd, int *fd)
{
	if (general->o_flag == 1)
	{
		re_out(node, general, save_fd);
		close(fd[0]);
		close(fd[1]);
	}
	else if (node->next == NULL || node->next->token == 1)
		piping(fd, save_fd, node, general);
	else if (node->next->token == 2 || node->next->token == 3)
		re_out(node, general, save_fd);
	else
	{
		if (node->builtin == 1 || node->builtin == 3 || node->builtin == 6)
		{
			builtinmanager(node, general);
			exit (g_last_exit_status);
		}
		execve(node->command2[0], node->command2, NULL);
	}
}

int	execute_command(t_lex *node, t_general *general, int *save_fd)
{
	int	pid;
	int	fd[2];
	int	status;

	if (node->builtin != 1 && node->builtin != 3
		&& node->builtin != 6 && node->builtin != 0)
	{
		builtinmanager(node, general);
		return (g_last_exit_status);
	}
	if (node->next && node->next->token == 1)
		if (pipe(fd) == -1)
			perror("pipe error\n");
	pid = fork();
	if (pid == 0)
		execute_command2(node, general, save_fd, fd);
	waitpid(pid, &status, 0);
	if (node->next && node->next->token == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

void	big_redir_finder(t_general *general)
{
	int		index_in;
	int		index_hd;

	index_hd = hd_manager(general);
	index_in = fd_redirin1(general);
	if (index_in > index_hd && index_in > -1)
	{
		dup2(general->input_fd, STDIN_FILENO);
		close(general->input_fd);
	}
	else if ((index_hd > index_in && index_hd > -1))
	{
		dup2(general->hd_fd, STDIN_FILENO);
		close(general->hd_fd);
	}
}

void	executor(t_general *general)
{
	t_lex	*tmp;
	int		save_fd[2];

	if (g_last_exit_status != 0 && g_last_exit_status != 130)
		return ;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	general->o_flag = re_dir_status(open_fd(general,
				find_correct_redir(general)), general);
	tmp = general->lexer;
	big_redir_finder(general);
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
	general->save_exit_status = g_last_exit_status;
}
