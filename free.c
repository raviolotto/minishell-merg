/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:33:03 by amema             #+#    #+#             */
/*   Updated: 2024/01/24 17:57:36 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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
	free_matrix(node->command2);
	free(node->command);
	free(node);
}

// void	free_matrix1(char **matrix)
// {
// 	int i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (matrix[i] != NULL)
// 	{
// 		while (matrix[i][j] != NULL)
// 		{
// 			free(matrix[i][j]);
// 			j++;
// 		}
// 		free(matrix[i]);
// 		i++;
// 	}
// 	free(matrix);
// }

void	free_lex(t_lex *node)
{
	if (node == NULL)
		return ;
	// +altra roba che devo freeare(?) ---->decidere se freeare con questo oppure afalcons
	free_matrix(&(node->command2));
	free_lex(node->next);
	// +altra roba che devo freeare(?)
	free_matrix(&(node->command)); 
	free(node);
}

void	free_general(t_general *general)
{
	free_matrix(&(general->envp2));
	free_matrix(&(general->enexp));
	free_matrix(&(general->path));
	//linkd list of t_lex IN t_general
	free_lex(general->lexer);
	free(general->flag_quotes);
}

