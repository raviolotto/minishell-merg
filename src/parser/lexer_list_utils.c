/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:12:07 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	pipe_status(t_general *general)
{
	t_lex	*tmp;
	int		i;

	tmp = general->lexer;
	i = 0;
	while (tmp)
	{
		if (tmp->token == 1)
			i++;
		tmp = tmp->next;
	}
	if (i == 1)
		return (0);
	tmp = general->lexer;
	while (tmp)
	{
		if (tmp->token == 1)
			i--;
		if (i == 0 && tmp->token == 1)
			tmp->pipe_status = 2;
		tmp = tmp->next;
	}
	return (0);
}

t_lex	*lex_last(t_lex *head)
{
	t_lex	*tmp;

	tmp = head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_lex	*new_lex_node(void)
{
	t_lex	*tmp;

	tmp = malloc(sizeof(t_lex));
	if (!tmp)
		return (NULL);
	else if (tmp)
	{
		tmp->token = 0;
		tmp->pipe_status = 0;
		tmp->arguments = NULL;
		tmp->builtin = -1;
		tmp->next = NULL;
	}
	return (tmp);
}

void	lex_add_last(t_lex *head, t_lex *new)
{
	t_lex	*tmp;

	tmp = lex_last(head);
	tmp->next = new;
	return ;
}
