/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:33 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_unsetenv(t_general *general, t_lex *node)
{
	int		i;
	int		j;
	int		index;
	char	**envtmp;

	index = my_setenv(node->arguments[1], NULL, &(general->environment_variables));
	if (index == -1)
		return ;
	envtmp = ft_calloc(matrixlen(general->environment_variables), sizeof(char *));
	i = 0;
	j = 0;
	while (general->environment_variables[i])
	{
		if (i == index)
			i++;
		if (general->environment_variables[i])
		{
			envtmp[j] = ft_strdup(general->environment_variables[i]);
			i++;
		}
		j++;
	}
	envtmp[j] == NULL;
	free_matrix(general->environment_variables);
	general->environment_variables = envtmp;
}

void	ft_unsetexp(t_general *general, t_lex *node)
{
	int		i;
	int		j;
	int		index;
	char	**envtmp;

	index = my_setenv(node->arguments[1], NULL, &(general->expanded_environment));
	if (index == -1)
		return ;
	envtmp = ft_calloc(matrixlen(general->expanded_environment), sizeof(char *));
	i = 0;
	j = 0;
	while (general->expanded_environment[i])
	{
		if (i == index)
			i++;
		if (general->expanded_environment[i])
		{
			envtmp[j] = ft_strdup(general->expanded_environment[i]);
			i++;
		}
		j++;
	}
	envtmp[j] == NULL;
	free_matrix(general->expanded_environment);
	general->expanded_environment = envtmp;
}

void	handle_unset(t_general *general, t_lex *node)
{
	if (!node->arguments[1])
		return ;
	ft_unsetenv(general, node);
	ft_unsetexp(general, node);
}
