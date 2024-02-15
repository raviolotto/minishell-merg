/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:58:58 by amema             #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	handle_echo(t_general *general, t_lex *node)
{
	int		no_newline;
	int		i;
	int		num_args;

	no_newline = 0;
	i = 1;
	num_args = matrixlen(node->arguments);
	while (node->arguments[i] != NULL && num_args > 1
		&& ft_strncmp(node->arguments[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}
	while (i < num_args)
	{
		if (node->arguments[i])
			ft_printf("%s", node->arguments[i]);
		if (i < num_args -1)
			ft_printf(" ");
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
}
