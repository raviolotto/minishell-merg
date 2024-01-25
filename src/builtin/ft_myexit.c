/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:43:41 by amema             #+#    #+#             */
/*   Updated: 2024/01/25 18:15:12 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	arg_error(char *first, char *var, char *secondigliano)
{
	ft_putstr_fd(first, 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(secondigliano, 2);
}

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
	if (only_n_in_str(args[1]))
	{
		if (len_args == 2)
		{
			exit_n = (ft_atoi(args[1]) % 256);
			// exit_n = exit_n % 256;
			if (exit_n < 0)
				exit_n = exit_n + 256;
			// arg_error("exit\n", NULL, NULL);
			// funzione per free-are exit
			printf("exit\n");
			exit(exit_n);
		}
		else
		{
			//arg_error("exit\n", NULL, NULL);
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			g_last_exit_status = 1; // variabile externa global
			// exit(g_last_exit_status);
		}
	}
	else
	{
		arg_error("exit\nminishell: exit: ",
			args[1], ": numeric argument required\n");
		g_last_exit_status = 2;
		exit(g_last_exit_status);
	}
}

void	handle_exit(char **args)
{
	int	len_args;
	int	exit_n;

	len_args = 1;
	exit_n = 0;
	if (args)
		while (args[len_args])
			len_args++;
	if (len_args == 1)
	{
		printf("exit\n");
		exit(g_last_exit_status);
	}
	else
		exit_utils(args, exit_n, matrixlen(args));
}
