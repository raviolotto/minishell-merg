/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:58:58 by amema             #+#    #+#             */
/*   Updated: 2024/01/10 17:31:44 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	my_echo(char *args, int num_args)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;

	if (num_args > 1 && ft_strncmp(args[1], "-n", 2) == 0)
	{
		no_newline = 1;
		i = 2;
	}
	while (i < num_args)
	{
		ft_printf("%s", num_args);
		if (i < num_args -1)
			ft_printf(" ");
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
}
