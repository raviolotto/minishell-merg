/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:01 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/19 17:32:47 by lmorelli         ###   ########.fr       */
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
	while(matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	return;
}

int	dumb_builtin_check(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (2);
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (3);
	else if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (4);
	else if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (5);
	else if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (6);
	else if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (7);
	else
		return (0);
}

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	i++;
	return (i);
}

char	**matrix_newline(char **matrix, char *str)
{
	int		len;
	char	**newmatrix;

	len = matrixlen(matrix);
	newmatrix = malloc((len + 2) * sizeof(char *));
	if(!newmatrix)
		perror("errore allocazione di memoria");
	len = 0;
	while(matrix[len] != NULL)
	{
		newmatrix[len] = ft_strdup(matrix[len]);
		len ++;
	}
	newmatrix[len] = str;
	newmatrix[len + 1] = NULL;
	free_matrix(matrix);
	return(newmatrix);
}

void	print_export(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	if (matrix == NULL)
		return;
	while(matrix[i] != NULL)
	{
		ft_printf("declare -x ");
		 j = 0;
		while(matrix[i][j])
		{
			write(1, &matrix[i][j], 1);
				if(matrix[i][j] == '=')
					write(1, "\"", 1);
			j++;
		}
		if(ft_strchr(matrix[i], '='))
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	return;
}