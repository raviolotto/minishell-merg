/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:58:58 by amema             #+#    #+#             */
/*   Updated: 2024/02/09 16:12:03 by lmorelli         ###   ########.fr       */
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
	num_args = matrixlen(node->command2);
	while (node->command2[i] != NULL && num_args > 1
		&& ft_strncmp(node->command2[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}
	while (i < num_args)
	{
		if (node->command2[i])
			ft_printf("%s", node->command2[i]);
		if (i < num_args -1)
			ft_printf(" ");
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
}
