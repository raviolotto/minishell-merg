/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:44:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/17 19:06:04 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	quotes(char *str, int j)
{
	int	j2;

	j2 = 0;
	if (str[j] == 34)
	{
		j2++;
		while (str[j + j2] != 34 && str[j + j2] != '\0')
			++j2;
		return (j2);
	}
	else if (str[j] == 39)
	{
		j2++;
		while (str[j + j2] != 39 && str[j + j2] != '\0')
			j2++;
		return (j2);
	}
	return (0);
}

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

t_lex	*noding(t_general *general)
{
	t_lex	*tmp;

	if (general->lexer == NULL)
	{
		tmp = new_lex_node();
		general->lexer = tmp;
	}
	else
	{
		tmp = new_lex_node();
		lex_add_last(general->lexer, tmp);
	}
	return (tmp);
}

int	menage_token(char *str, int i, t_general *general, int *p)
{
	t_lex	*tmp;
	int		j;

	j = 1;
	tmp = noding(general);
	tmp->token = what_token(str, i);
	if (tmp ->token == 1)
	{
		tmp->pipe_status = *p;
		if (*p == 0)
			*p = 1;
		tmp->command = ft_substr(str, i, j);
		return (j);
	}
	else if (tmp->token == 3 || tmp->token == 5)
		j++;
	while (what_token(str, i + j) == 0 && str[i + j] != '\0')
	{
		if (str[i + j] == 34 || str[i + j] == 39)
			j += quotes(str, j);
		j++;
	}
	tmp->command = ft_substr(str, i, j);
	return (j);
}
