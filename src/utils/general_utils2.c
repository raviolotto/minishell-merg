/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:14:37 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/08 19:32:21 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	is_whitespace_input(const char *str)
{
	while (*str)
	{
		if (iswhite(*str))
			return (0);
		str++;
	}
	return (1);
}

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		ft_printf("%s\n", matrix[i]);
		i++;
	}
	return ;
}

int	dumb_builtin_check(char *command)
{
	int	i;

	i = ft_strlen(command);
	if (ft_strncmp(command, "echo", i) == 0 && i == 4)
		return (1);
	else if (ft_strncmp(command, "cd", i) == 0 && i == 2)
		return (2);
	else if (ft_strncmp(command, "pwd", i) == 0 && i == 3)
		return (3);
	else if (ft_strncmp(command, "export", i) == 0 && i == 6)
		return (4);
	else if (ft_strncmp(command, "unset", i) == 0 && i == 5)
		return (5);
	else if (ft_strncmp(command, "env", i) == 0 && i == 3)
		return (6);
	else if (ft_strncmp(command, "exit", i) == 0 && i == 4)
		return (7);
	else
		return (0);
}
