/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:12:51 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/01 16:12:53 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	show_quotes_error(char *word)
{
	g_last_exit_status = 1;
	ft_putstr_fd("kitty shell: you didn't close the ", 2);
	if (word[0] == '\'')
		ft_putstr_fd("\'\n", 2);
	else
		ft_putstr_fd("\"\n", 2);
}

int	handle_quotes(char *word)
{
	int	i;

	i = -1;
	while (word[++i] != '\0')
	{
		if (word[i] == '\'')
		{
			if ((ft_nb_quotes(word + i, '\'') % 2) == 0)
			{
				show_quotes_error(word);
				return (1);
			}
			return (0);
		}
		else if (word[i] == '\"')
		{
			if ((ft_nb_quotes(word + i, '\"') % 2) == 0)
			{
				show_quotes_error(word);
				return (1);
			}
			return (0);
		}
	}
	return (0);
}

void	show_pathfinder_error(char *command)
{
	g_last_exit_status = 127;
	ft_putstr_fd("kitty shell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found \n", 2);
}

void	manage_memory_error(void)
{
	g_last_exit_status = 1;
	ft_putstr_fd("Error in memory allocation /n", 2);
	exit(EXIT_FAILURE);
}
