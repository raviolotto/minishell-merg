/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:29:54 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/03 14:21:54 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/mini_shell.h"

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
	while(tmp != NULL && tmp->i <= pipe_pos)
	{
		if(tmp->token == 3 || tmp->token == 2)
			redir_pos = tmp->i;
		tmp = tmp->next;
	}
	if(redir_pos > -1)
		return (redir_pos);
	while(tmp != NULL)
	{
		if(tmp->token == 3 || tmp->token == 2)
			redir_pos = tmp->i;
		tmp = tmp->next;
	}
	return (redir_pos);
}

void	open_fd(t_general *general, int i)
{
	t_lex	*node;
	int		file;

	node = general->lexer;
	while(node != NULL)
	{
		if(node->token == 2)
		{
			file = open(node->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if(i == node->i)
				{
					general->file_fd = file;
					return ;
				}
			close (file);
		}
		else if(node->token == 3)
		{
			file = open(node->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if(i == node->i)
				{
					general->file_fd = file;
					return ;
				}
			close (file);
		}
		node = node->next;
	}
}

//NON ELIMINARE
// void	open_fd(t_general *general, int i)
// {
// 	t_lex	*node;
// 	int		file;

// 	node = general->lexer;
// 	while(node != NULL)
// 	{
// 		if(node->token == 2)
// 		{
// 			file = open(node->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 			if(i == node->i)
// 					general->file_fd = file;
// 			else
// 			close (file);
// 		}
// 		else if(node->token == 3)
// 		{
// 			file = open(node->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 			if(i == node->i)
// 					general->file_fd = file;
// 			else
// 			close (file);
// 		}
// 		node = node->next;
// 	}
// }
