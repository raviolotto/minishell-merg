/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:29 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/15 19:49:01 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void expander(t_general *general)
{
	t_lex *tmp;
	int i;
	int index;
	
	tmp = general->lexer;
	while(tmp)
	{
		i = 0;
		while(tmp->command2[i])
		{
			if(tmp->command2[i][0] == '$')
			{	
				index = my_setenv(&tmp->command2[i][1], NULL, &general->envp2);
				if (index >= 0) 
				{
					free(tmp->command2[i]);	
					tmp->command2[i] = ft_strdup(ft_strchr(general->envp2[index], '=')  + 1);
				}
				else if (index == -1)
				{
					free(tmp->command2[i]);
					tmp->command2[i] = ft_strdup("");
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}

// void expander(t_general *general)
// {
// 	t_lex *tmp;
// 	int i;
// 	int index;
// 	char	*euro;
	
// 	tmp = general->lexer;
// 	while(tmp)
// 	{
// 		i = 0;
// 		while(tmp->command2[i])
// 		{
// 			euro = ft_strchr(tmp->command2[i], '$');
// 			if(euro != NULL)
// 			{	
// 				index = my_setenv(euro + 1, NULL, &general->envp2);
// 				if (index >= 0) 
// 				{
// 					free(euro);	
// 					euro = ft_strdup(ft_strchr(general->envp2[index], '=')  + 1);
// 				}
// 				else if (index == -1)
// 				{
// 					free(euro);
// 					euro = ft_strdup("");
// 				}
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }