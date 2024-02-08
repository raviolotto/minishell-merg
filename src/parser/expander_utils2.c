/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:32:40 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/08 17:35:05 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*calcolate_parte_prima(char **parte_prima, char *input, char *posizione)
{
	int		len;

	len = posizione - input;
	*parte_prima = ft_substr(input, 0, len);
	return (*parte_prima);
}

char	*calcolate_parte_dopo(char **second_part, char *fine_comando)
{
	int		len;

	len = strlen(fine_comando);
	*second_part = ft_substr(fine_comando, 0, len);
	return (*second_part);
}

char	*find_fine_comando(char *posizione)
{
	char	*fine_comando;

	fine_comando = posizione + ft_strlen("$");
	while (*fine_comando != ' ' && *fine_comando != '\0'
		&& *fine_comando != '\"' && *fine_comando != '$'
		&& *fine_comando != '\'')
	{
		if (*fine_comando == '?')
		{
			if (*fine_comando + 1 == '\0')
				return (fine_comando + 2);
			else
				return (fine_comando + 1);
		}
		fine_comando++;
	}
	return (fine_comando);
}
