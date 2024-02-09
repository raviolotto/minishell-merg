/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:44:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/09 17:59:46 by lmorelli         ###   ########.fr       */
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

int	menage_token3(t_lex	*tmp, char *str, int i, int j)
{
	while (what_token(str, i + j) == 0 && str[i + j] != '\0')
	{
		if (str[i + j] == 34 || str[i + j] == 39)
			j += quotes(str, j);
		j++;
	}
	tmp->command = ft_substr(str, i, j);
	return (j);
}

int	menage_token2(t_lex *tmp, char *str, int i, int j)
{
	while (iswhite(str[i + j]) == 0)
		j++;
	if (what_token(str, i + j) != 0 || str[i + j] == '\0')
	{
		g_last_exit_status = 2;
		ft_printf("parse error\n");
	}
	while (what_token(str, i + j) == 0
		&& str[i + j] != '\0' && iswhite(str[i + j]) == 1)
	{
		if (str[i + j] == 34 || str[i + j] == 39)
			j += quotes(str, j);
		j++;
	}
	tmp->command = ft_substr(str, i, j);
	return (j);
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
	if (tmp->token != 0 && tmp->token != 1)
		j = menage_token2(tmp, str, i, j);
	else
		j = menage_token3(tmp, str, i, j);
	return (j);
}
