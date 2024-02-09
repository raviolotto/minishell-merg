/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:02 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/09 16:11:15 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	find_redir_in(t_general *general)
{
	t_lex	*node;
	int		i;

	i = -1;
	node = general->lexer;
	while (node)
	{
		if (node->token == 4)
			i = node->i;
		node = node->next;
	}
	return (i);
}

int	fd_redirin2(t_general *general, int index, t_lex *node)
{
	int	file;

	file = 0;
	while (node != NULL)
	{
		if (node->token == 4)
		{
			file = open(node->command, O_RDONLY);
			if (file < 0)
			{
				ft_putstr_fd("Error opening the file\n", 2);
				g_last_exit_status = 1;
				return (-1);
			}
			if (index == node->i)
				general->input_fd = file;
			else
				close(file);
		}
		node = node->next;
	}
}

int	fd_redirin1(t_general *general)
{
	t_lex	*node;
	int		index;

	node = general->lexer;
	index = find_redir_in(general);
	if (index == -1)
		return (-1);
	if (fd_redirin2(general, index, node) == -1)
		return (-1);
	return (index);
}
