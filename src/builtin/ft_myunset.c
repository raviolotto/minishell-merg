/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myunset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:33 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/15 14:47:40 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	handle_unset(t_general *general, t_lex *node)
{
	int		i;
	int 	j;
	int		index;
	char	**envtmp;

	if (node->command2[1] == NULL || (index = my_setenv(node->command2[1], NULL, &(general->envp2))) == -1)
		return ;
	envtmp = ft_calloc(matrixlen(general->envp2) - 1, sizeof(char *));
	i = 0;
	j = 0;
	while (general->envp2[i])
	{
		if(i == index)
			i++;
		envtmp[j] = ft_strdup(general->envp2[i]);
		i++;
		j++;
	}
	free_matrix(general->envp2);
	general->envp2 = envtmp;
}
