/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:43:41 by amema             #+#    #+#             */
/*   Updated: 2024/01/16 19:34:31 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	only_n_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_utils(char **args, int exit_n, int len_args)
{
	if(only_n_in_str(args[1]))
	{
		if (len_args == 2)
		{
			exit_n = ft_atoi(args[1]);
			exit_n = exit_n % 256;
			if (exit_n < 0)
				exit_n = exit_n + 256;
			ft_printf("exit\n");
			// funzione per free-are exit

		}
		else
		{
			ft_putstr_fd ("exit\nminishell: exit: too many arguments\n", 2); //2 = stderror
			g_last_exit_status = 1; // variabile externa global
		}
	}
	else
	{
		ft_putstr_fd ("kitty shell : exit: %s: numeric argument required\n", 2);
		exit(130);		
	}
}
void	handle_exit(char **args)
{
	int	exit_n;

	exit_n = 0;
	// if (args)
	// {
	// 	while(args[i])
	// 		i++;
	// }
	// if (i == 0)
	if(!args[1])
	{
		ft_printf("exit\n");
		//free di tuttoooooooooo 
		exit(g_last_exit_status);
		// free exit
	}
	else
		exit_utils(args, exit_n, matrixlen(args));
}