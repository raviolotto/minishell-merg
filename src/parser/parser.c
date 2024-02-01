/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:23:21 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 16:01:36 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	what_token(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (3);
		return (2);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (5);
		return (4);
	}
	return (0);
}

int	iswhite(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (0);
	else
		return (1);
}

int	lexer(t_general *general)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (general->args[i] != '\0')
	{
		while (iswhite(general->args[i]) == 0)
			i++;
		i += menage_token(general->args, i, general, &p);
	}
	pipe_status(general);
	return (i);
}

int	parser(t_general *general)
{
	lexer(general);
	if (list_commander(general) == 1)
		return (1);
	return (0);
}
