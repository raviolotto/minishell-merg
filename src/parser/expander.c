/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:29 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/16 17:55:37 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*ft_str_dollar_cpy(char *src)
{
	int		a;
	char	*dest;

	dest = malloc(sizeof (char *) * ft_strlen(src) + 1);
	if(!dest)
		return (NULL);
	a = 0;
	while (src[a])
	{
		if (src[a] == '$')
			return (dest);
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

void expander(t_general *general)
{
	t_lex	*tmp;
	int		i;
	int 	index;
	int		j;
	int 	flag = 0;
	int 	idx = 0;
	char	*dollar;
	char	*euro;
	
	tmp = general->lexer;
	while(tmp)
	{
		i = 0;
		while(tmp->command2[i])
		{	
			j = 0;
			while(tmp->command2[i][j] != '\0')
			{
				idx = ft_idx_quotes(tmp->command2[i], '$');
				if(ft_strchr(tmp->command2[i], '$' ) && idx != 0)
				{
					dollar = ft_str_dollar_cpy(tmp->command2[i]);
					flag = 1;
				}
				j++;
			}
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
			else if (flag == 1)
			{	
				euro = ft_strchr(tmp->command2[i], '$');
				index = my_setenv(euro + 1, NULL, &general->envp2);
				if (index >= 0)
				{
				free(tmp->command2[i]);	
				tmp->command2[i] = ft_strjoin(dollar,  ft_strdup(ft_strchr(general->envp2[index], '=')  + 1));
				}
				else if (index == -1)
				{
					free(tmp->command2[i]);
					tmp->command2[i] = ft_strjoin(dollar, "");
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
