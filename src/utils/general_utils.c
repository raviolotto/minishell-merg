/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:01 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/17 17:30:53 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free (matrix[i]);
		i++;
	}
	free (matrix);
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

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	return ;
}

int	dumb_builtin_check(char *command)
{
	int	i;

	i = ft_strlen(command);
	if (ft_strncmp(command, "echo", i) == 0 && i == 4)
		return (1);
	else if (ft_strncmp(command, "cd", i) == 0 && i == 2)
		return (2);
	else if (ft_strncmp(command, "pwd", i) == 0 && i == 3)
		return (3);
	else if (ft_strncmp(command, "export", i) == 0 && i == 6)
		return (4);
	else if (ft_strncmp(command, "unset", i) == 0 && i == 5)
		return (5);
	else if (ft_strncmp(command, "env", i) == 0 && i == 3)
		return (6);
	else if (ft_strncmp(command, "exit", i) == 0 && i == 4)
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
	if (!newmatrix)
		perror("errore allocazione di memoria");
	len = 0;
	while (matrix[len] != NULL)
	{
		newmatrix[len] = ft_strdup(matrix[len]);
		len ++;
	}
	newmatrix[len] = str;
	newmatrix[len + 1] = NULL;
	free_matrix(matrix);
	return (newmatrix);
}

void	print_export(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		ft_printf("declare -x ");
		j = 0;
		while (matrix[i][j])
		{
			write(1, &matrix[i][j], 1);
			if (matrix[i][j] == '=')
				write(1, "\"", 1);
			j++;
		}
		if (ft_strchr(matrix[i], '='))
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	return ;
}
//questa funzione deve essere nello stesso file di minisplit
static size_t	ft_counter(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			++count;
			while (s[i] && s[i] != c)
				++i;
		}
		else
			i++;
	}
	return (count);
}

int	handle_token(const char **s, char c, char ***matrix, size_t *i)
{
	size_t	j;

	j = 0;

	while (**s && **s != c && ++j)
	{
		if (**s == 34 || **s == 39)
		{
			j += quotes((char *)*s, 0);
			*s += quotes((char *)*s, 0);
		}
		++(*s);
	}
	(*matrix)[(*i)++] = ft_substr(*s - j, 0, j);
	return (j);
}

char **maxxisplit(char const *s, char c)
{
	char	**matrix;
	size_t	i;

	if (!s)
		return (NULL);

	i = 0;
	matrix = malloc(sizeof(char *) * (ft_counter(s, c) + 1));
	if (!matrix)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			handle_token(&s, c, &matrix, &i);
		}
		else
			++s;
	}
	matrix[i] = 0;
	return (matrix);
}
