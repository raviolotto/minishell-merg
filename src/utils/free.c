/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:01:40 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
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

void	afalcons(t_lex *node)
{
	if (node->next)
		afalcons(node->next);
	free_matrix(node->arguments);
	free(node->main_command);
	free(node);
}

void	free_lex(t_lex *node)
{
	if (node == NULL)
		return ;
	if (node->next)
		free_lex(node->next);
	if (node->arguments != NULL)
		free_matrix(node->arguments);
	free(node->main_command);
	free(node);
}

void	free_general(t_general *general)
{
	free_matrix(general->environment_variables);
	free_matrix(general->expanded_environment);
	if (general->path != NULL)
		free_matrix(general->path);
}

void	free_and_exit(int exit_n, t_general *general)
{
	if (general != NULL)
	{
		free_general(general);
		free_lex(general->lexer);
	}
	clear_history();
	exit(exit_n);
}
