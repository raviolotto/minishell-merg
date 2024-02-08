/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:25:03 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/08 17:39:30 by lmorelli         ###   ########.fr       */
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

void	index_list(t_general *general)
{
	t_lex	*tmp;
	int		i;

	tmp = general->lexer;
	i = 0;
	while (tmp != NULL)
	{
		tmp->i = i++;
		tmp = tmp->next;
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	size;
	int		i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen(s1)) + (ft_strlen(s2)) + 1;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[j++] = s1[i];
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	free(s1);
	return (str);
}
