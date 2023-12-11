/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:01 by jcardina          #+#    #+#             */
/*   Updated: 2023/11/24 14:36:03 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	while(matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**matrix_dup(char **matrix)
{
	char	**ret;
	size_t	i;

	i = 0;
	while(matrix[i] != NULL)
		i++;
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while(matrix[i] != NULL)
	{
		ret[i] = ft_strdup(matrix[i]);
		i++;
	}
	return (ret);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return;
	while(matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	return;
}