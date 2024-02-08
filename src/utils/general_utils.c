/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:33:01 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/08 19:32:09 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	**matrix_newline(char **matrix, char *str)
{
	int		len;
	char	**newmatrix;

	len = matrixlen(matrix);
	newmatrix = malloc((len + 2) * sizeof(char *));
	if (!newmatrix)
	{
		g_last_exit_status = 1;
		ft_putstr_fd("kitty shell: error while allocating memory\n", 2);
	}
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

char	**maxxisplit(char const *s, char c)
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
