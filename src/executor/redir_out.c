/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:29:54 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/08 18:09:55 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	find_correct_redir(t_general *general)
{
	int		pipe_pos;
	int		redir_pos;
	t_lex	*tmp;

	redir_pos = -1;
	tmp = general->lexer;
	while (tmp->token != 1 && tmp->next != NULL)
		tmp = tmp->next;
	pipe_pos = tmp->i;
	tmp = general->lexer;
	while (tmp != NULL && tmp->i <= pipe_pos)
	{
		if (tmp->token == 3 || tmp->token == 2)
			redir_pos = tmp->i;
		tmp = tmp->next;
	}
	if (redir_pos > -1)
		return (redir_pos);
	while (tmp != NULL)
	{
		if (tmp->token == 3 || tmp->token == 2)
			redir_pos = tmp->i;
		tmp = tmp->next;
	}
	return (redir_pos);
}

int	open_fd(t_general *general, int i)
{
	t_lex	*node;
	int		file;

	node = general->lexer;
	while (node != NULL)
	{
		if (node->token == 2)
		{
			file = open(node->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (i == node->i)
				general->file_fd = file;
			else
				close(file);
		}
		else if (node->token == 3)
		{
			file = open(node->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (i == node->i)
				general->file_fd = file;
			else
				close(file);
		}
		node = node->next;
	}
	return (i);
}

int	re_dir_status(int index, t_general *general)
{
	t_lex	*tmp;
	int		pipe_pos;

	if (index == -1)
		return (-1);
	tmp = general->lexer;
	while (tmp->token != 1 && tmp->next != NULL)
		tmp = tmp->next;
	pipe_pos = tmp->i;
	if (index < pipe_pos)
		return (1);
	else
		return (2);
}

int	re_out(t_lex *node, t_general *general, int *save_fd)
{
	dup2(general->file_fd, STDOUT_FILENO);
	close(general->file_fd);
	if (node->builtin > 0)
	{
		builtinmanager(node, general);
		dup2(save_fd[1], STDOUT_FILENO);
		exit (g_last_exit_status);
	}
	execve(node->command2[0], node->command2, NULL);
}
