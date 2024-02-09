/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:32:40 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/09 16:37:12 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*calculate_first_part(char **first_part, char *input, char *position)
{
	int		len;

	len = position - input;
	*first_part = ft_substr(input, 0, len);
	return (*first_part);
}

char	*calculate_final_part(char **second_part, char *end_command)
{
	int		len;

	len = strlen(end_command);
	*second_part = ft_substr(end_command, 0, len);
	return (*second_part);
}

char	*find_end_command(char *position)
{
	char	*end_command;

	end_command = position + ft_strlen("$");
	while (*end_command != ' ' && *end_command != '\0'
		&& *end_command != '\"' && *end_command != '$'
		&& *end_command != '\'')
	{
		if (*end_command == '?')
		{
			if (*end_command + 1 == '\0')
				return (end_command + 2);
			else
				return (end_command + 1);
		}
		end_command++;
	}
	return (end_command);
}
