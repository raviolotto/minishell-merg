/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:43:41 by amema             #+#    #+#             */
/*   Updated: 2024/01/14 18:10:46 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	only_n_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_utils(char **args, int exit_n, int len_args)
{
	if (only_n_in_str(args[0]))
	{
		if (len_args == 1)
		{
			exit_n = ft_atoi(args[0]);
			exit_n = exit_n % 256;
			if (exit_n < 0)
				exit_n = exit_n + 256;
			ft_printf("exit\n");
			// funzione per free-are exit
		}
		else
		{
			ft_putstr_fd ("exit\nminishell: exit: too many arguments\n", 2); //2 = stderror
			last_exit_status = 1; // variabile externa global
		}
	}
	else
	{
		perror("Error");
	}
}
