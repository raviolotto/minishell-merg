/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:29 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/19 14:29:22 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*ft_str_dollar_cpy(char *src)
{
	int		a;
	char	*dest;

	dest = malloc(sizeof (char *) * ft_strlen(src) + 1);
	if (!dest)
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
/*
appunti expander status

funzione che controlla il $?
comando scsd$?        output  = scsd0
comando $?            "       = 0
comando ciao$?ciao    "       = ciao0ciao

il return deve essere 0 se la funzione non ha espanso il punto interrogativo
altrimenti 1 se lo espande
in dollar é gia storato la parte prima del punto interrogativo, il problema sarebbe il terzo esempio
*/

int	expander_status(char **line, char *dollar)
{
	int	i;
	char	*euro;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = -1;
	while(line[0][++i] != '\0')
	{
		euro = strchr(*line, '$');
		if(euro && (*(euro + 1) == '?'))
		{
			tmp = ft_itoa(g_last_exit_status);
			tmp2 = euro + 2;
			if (dollar)
				tmp3 = ft_strjoin(dollar, tmp);
			else
				tmp3 = tmp;
			tmp3 = ft_strjoin(tmp3, tmp2);
			free(*line);
			*line = tmp3;
			return (1);
		}
	}
	return(0);
}

void	ft_expander_case2(char **line, t_general *general, char *dollar)
{
	char	*euro;
	int		index;

	euro = ft_strchr(*line, '$');
		index = my_setenv(euro + 1, NULL, &general->envp2);
		if (index >= 0)
		{
			free (*line);
			*line = ft_strjoin(dollar, ft_strdup(ft_strchr(general->envp2[index], '=') + 1));
			return ;
		}
			free(*line);
			*line = ft_strjoin(dollar, "");
}

void	ft_expander_case(char **line, int flag, t_general *general, char *dollar)
{
	int		index;

	if (line[0][0] == '$')
	{
		index = my_setenv(&line[0][1], NULL, &general->envp2);
		if (index >= 0)
		{
			free(*line);
			*line = ft_strdup(ft_strchr(general->envp2[index], '=') + 1);
			return ;
		}
		free(*line);
		*line = ft_strdup("");
		return ;
	}
	else if (flag == 1)
	{
		ft_expander_case2(line, general, dollar);
	}
}

void	node_expander(char **command2, t_general *general)
{
	int		i;
	int		j;
	int		idx;
	int		flag;
	char	*dollar;

	i = -1;
	flag = 0;
	while(command2[++i])
	{
		j = 0;
		while (command2[i][j] != '\0')
		{
			idx = ft_idx_quotes(command2[i], '$');
			if (ft_strchr(command2[i], '$') && idx != 0)
			{
				dollar = ft_str_dollar_cpy(command2[i]);
				flag = 1;
			}
			j++;
		}
		if(expander_status(&command2[i], dollar) == 0)
			ft_expander_case(&command2[i], flag, general, dollar);
	}
	free(dollar);
}
//modificare per far funzionare $PWD$PWD

void	expander(t_general *general)
{
	t_lex	*tmp;

	tmp = general->lexer;
	while(tmp)
	{
		node_expander(tmp->command2, general);
		tmp = tmp->next;
	}
}
// void	expander(t_general *general)
// {
// 	t_lex	*tmp;
// 	int		i;
// 	int		index;
// 	int		j;
// 	int		flag = 0;
// 	int		idx = 0;
// 	char	*dollar;
// 	char	*euro;

// 	tmp = general->lexer;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->command2[i])
// 		{
// 			j = 0;
// 			while (tmp->command2[i][j] != '\0')
// 			{
// 				idx = ft_idx_quotes(tmp->command2[i], '$');
// 				if (ft_strchr(tmp->command2[i], '$' ) && idx != 0)
// 				{
// 					dollar = ft_str_dollar_cpy(tmp->command2[i]);
// 					flag = 1;
// 				}
// 				j++;
// 			}
// 			if (tmp->command2[i][0] == '$')
// 			{
// 				index = my_setenv(&tmp->command2[i][1], NULL, &general->envp2);
// 				if (index >= 0)
// 				{
// 					free(tmp->command2[i]);
// 					tmp->command2[i] = ft_strdup(ft_strchr(general->envp2[index], '=') + 1);
// 				}
// 				else if (index == -1)
// 				{
// 					free(tmp->command2[i]);
// 					tmp->command2[i] = ft_strdup("");
// 				}
// 			}
// 			else if (flag == 1)
// 			{
// 				euro = ft_strchr(tmp->command2[i], '$');
// 				index = my_setenv(euro + 1, NULL, &general->envp2);
// 				if (index >= 0)
// 				{
// 					free(tmp->command2[i]);
// 					tmp->command2[i] = ft_strjoin(dollar,  ft_strdup(ft_strchr(general->envp2[index], '=') + 1));
// 				}
// 				else if (index == -1)
// 				{
// 					free(tmp->command2[i]);
// 					tmp->command2[i] = ft_strjoin(dollar, "");
// 					free(dollar);
// 				}
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }
