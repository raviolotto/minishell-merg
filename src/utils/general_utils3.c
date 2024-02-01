/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:25:03 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/01 17:40:32 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*cleaner(char *str)
{
	char	*new;

	if (str[0] == '\'')
		new = ft_strtrim(str, "\'");
	else
		new = ft_strtrim(str, "\"");
}

void	file_name_handler(t_lex *node)
{
	char	*str;
	char	*tmp;

	if (node->token == 3 || node->token == 5)
	{
		str = node->command + 2;
		str = ft_strtrim(str, " ");
		tmp = cleaner(str);
		free(str);
		free(node->command);
		node->command = tmp;
	}
	else
	{
		str = node->command + 1;
		str = ft_strtrim(str, " ");
		tmp = cleaner(str);
		free(str);
		free(node->command);
		node->command = tmp;
	}
}

char	**matrix_dup(char **matrix)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		ret[i] = ft_strdup(matrix[i]);
		i++;
	}
	return (ret);
}
