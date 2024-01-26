/* ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:22 by amema             #+#    #+#             */
/*   Updated: 2024/01/26 14:21:32 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************** */

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
	free_matrix(node->command2);
	free(node->command);
	free(node);
}

void	free_lex(t_lex *node)
{

	if (node == NULL)
		return ;
	// +altra roba che devo freeare(?) ---->decidere se freeare con questo oppure afalcons
	if (node->next)
		free_lex(node->next);
	// +altra roba che devo freeare(?)
	free_matrix(node->command2);
	free(node->command);
	free(node);
}

void	free_general(t_general *general)
{
	free_matrix(general->envp2);
	free_matrix(general->enexp);
	free_matrix(general->path);
	//da vedere quando si fará il calloc di array di int
	//free(general->flag_quotes);
}

void	free_and_exit(int exit_n, t_general *general)
{
	//int str;
	if (general != NULL)
	{
		free_general(general); //free_di_Tutto
		free_lex(general->lexer);
	}
	 exit(exit_n);
}
