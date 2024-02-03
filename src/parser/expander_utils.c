/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:32:40 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/03 16:52:01 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	confronta_sottostringhe(const char *str, const char *sub, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] != sub[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*find_substring_position(const char *str, const char *sub)
{
	size_t	len;

	len = ft_strlen(sub);
	while (*str != '\0')
	{
		if (confronta_sottostringhe(str, sub, len))
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*find_sostituzione(char *comando, t_general *general)
{
	int		index;
	char	*sostituzione;

	if (strncmp(comando, "$?", 2) == 0)
	{
		if(g_last_exit_status == 130 || g_last_exit_status == 0);
			general->save_exit_status = 130;
		sostituzione = ft_itoa(general->save_exit_status);
		return (sostituzione);
	}
	else
	{
		index = my_setenv(comando + 1, NULL, &general->envp2);
		if (index >= 0)
		{
			sostituzione = ft_strchr(general->envp2[index], '=') + 1;
			return (sostituzione);
		}
		else
		{
			return ("");
		}
	}
}
