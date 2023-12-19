/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myunset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:33 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/19 17:48:42 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

// int ft_unsetexp(char *name, t_general *general)
// {
// 	int i;
// 	int j;

// 	i = 0;
//     while (general->enexp[i])
// 	{
//         if (ft_strncmp(general->enexp[i], name, ft_strlen(name)) == 0)// && general->enexp[i][ft_strlen(name)] == '=')
// 		{
// 			j = i;
//             while (general->enexp[j])
// 			{
//                 general->enexp[j] = general->enexp[j + 1];
// 				j++;
//             }
//             return (0);
//         }
// 		i++;
//     }
//     return (1);
// }

// int ft_unsetenv(char *name, t_general *general)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	if (ft_unsetexp(name, general) == 0){
// 	while (general->envp2[i])
// 	{
// 		if (ft_strncmp(general->envp2[i], name, ft_strlen(name)) == 0 && (general->envp2[i][ft_strlen(name)] == '='))
// 		{
// 			j = i;
// 			while (general->envp2[j])
// 			{
// 				general->envp2[j] = general->envp2[j + 1];
// 				j++;
// 			}
// 			return (0);
// 		}
// 		i++;
// 	}}
// 	return (1);
// }


// void	handle_unset(t_general *general, t_lex *node)
// {
// 	if (node->command2[1] == NULL)
// 		return ;
// 	if (ft_unsetenv(node->command2[1], general) == 0)
// 		return ;
// 	else
// 		printf("bash: unset: `%s': not a valid identifier\n", node->command2[1]);
// }


void	ft_unsetenv(t_general *general, t_lex *node)
{
	int		i;
	int 	j;
	int		index;
	char	**envtmp;

	if (node->command2[1] == NULL || (index = my_setenv(node->command2[1], NULL, &(general->envp2))) == -1)
		return ;
	envtmp = ft_calloc(matrixlen(general->envp2), sizeof(char *));
	i = 0;
	j = 0;
	while (general->envp2[i])
	{
		if(i == index)
			i++;
		if(general->envp2[i])
		{
			envtmp[j] = ft_strdup(general->envp2[i]);
			i++;
		}
			j++;
	}
	envtmp[j] == NULL;
	free_matrix(general->envp2);
	general->envp2 = envtmp;
}

void	ft_unsetexp(t_general *general, t_lex *node)
{
	int		i;
	int 	j;
	int		index;
	char	**envtmp;

	if (node->command2[1] == NULL || (index = my_setenv(node->command2[1], NULL, &(general->enexp))) == -1)
		return ;
	envtmp = ft_calloc(matrixlen(general->enexp), sizeof(char *));
	i = 0;
	j = 0;
	while (general->enexp[i])
	{
		if(i == index)
			i++;
		if(general->enexp[i])
		{
			envtmp[j] = ft_strdup(general->enexp[i]);
			i++;
		}
			j++;
	}
	envtmp[j] == NULL;
	free_matrix(general->enexp);
	general->enexp = envtmp;
}

void	handle_unset(t_general *general, t_lex *node)
{
	ft_unsetenv(general, node);
	ft_unsetexp(general, node);
}	