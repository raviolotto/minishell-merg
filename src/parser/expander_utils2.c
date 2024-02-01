/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:32:40 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/01 17:41:30 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*calcolate_parte_prima(char *input, char *posizione)
{
	char	*parte_prima;
	int		lunghezza_parte_prima;

	lunghezza_parte_prima = posizione - input;
	parte_prima = ft_substr(input, 0, lunghezza_parte_prima);
	return (parte_prima);
}

char	*calcolate_parte_dopo(char *fine_comando)
{
	char	*parte_dopo;
	int		lunghezza_parte_dopo;

	lunghezza_parte_dopo = strlen(fine_comando);
	parte_dopo = ft_substr(fine_comando, 0, lunghezza_parte_dopo);
	return (parte_dopo);
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
			if (*fine_comando + 1 == '\0')
				return (fine_comando + 2);
		else
			return (fine_comando + 1);
		fine_comando++;
	}
	return (fine_comando);
}
