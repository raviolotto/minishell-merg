/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:32:40 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/09 16:39:20 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	compare_substrings(const char *str, const char *sub, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] != sub[i])
			return (0);
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
		if (compare_substrings(str, sub, len))
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*find_substitution(char *command, t_general *general)
{
	int		index;
	char	*replacement;

	if (strncmp(command, "$?", 2) == 0)
	{
		if (g_last_exit_status == 130)
			general->save_exit_status = 130;
		replacement = ft_itoa(general->save_exit_status);
		return (replacement);
	}
	else
	{
		index = my_setenv(command + 1, NULL, &general->envp2);
		if (index >= 0)
		{
			replacement = ft_strchr(general->envp2[index], '=') + 1;
			return (replacement);
		}
		else
		{
			return ("");
		}
	}
}
