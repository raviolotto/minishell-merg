/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:29 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/24 19:04:55 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	confronta_sottostringhe(const char *str, const char *sub, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] != sub[i]) 
		{
			return (0); 
		}
		i++;
	}
	return (1);
}

char	*find_substring_position(const char *str, const char *sub)
{
	size_t	len;

	len = ft_strlen(sub);
	while (*str != '\0') 
	{
		if (confronta_sottostringhe(str, sub, len))
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

char	*find_sostituzione(char *comando, t_general *general)
{
	int		index;
	char	*sostituzione;

	if (strncmp(comando, "$?", 2) == 0)
	{
		sostituzione = ft_itoa(g_last_exit_status);
		return (sostituzione);
	}
	else 
	{
		index = my_setenv(comando + 1, NULL, &general->envp2);

		if (index >= 0)
		{
			sostituzione = ft_strchr(general->envp2[index], '=') + 1;
			return (sostituzione);
		}
		else
		{
			return ("");
		}
	}
}

char	*sostituisci_comando_dollaro(char *input, t_general *general)
{
	char	*posizione;
	char	*fine_comando;
	int		lunghezza_comando;
	char	*comando;
	char	*parte_prima;
	char	*parte_dopo;
	char	*updated_input;

	posizione = input;
	while (1)
	{
		posizione = find_substring_position(posizione, "$");
		if (posizione == NULL)
			break ;

		fine_comando = posizione + ft_strlen("$");

		while (*fine_comando != ' ' && *fine_comando != '\0' 
			&& *fine_comando != '\"' && *fine_comando != '$'
			&& *fine_comando != '\'')
		{
			fine_comando++;
		}
		lunghezza_comando = fine_comando - posizione;
		comando = ft_substr(posizione, 0, lunghezza_comando);
		parte_prima = ft_substr(input, 0, posizione - input);
		parte_dopo = ft_substr(fine_comando, 0, strlen(fine_comando));
		updated_input = 
			ft_strjoin(parte_prima, find_sostituzione(comando, general));
		updated_input = ft_strjoin(updated_input, parte_dopo);
		free(input);
		free(parte_prima);
		free(parte_dopo);
		free(comando);
		return (sostituisci_comando_dollaro(updated_input, general));
	}
	return (input);
}

void	ft_expander_case(char **line,t_general *general)
{
	char	*finale;

	finale = sostituisci_comando_dollaro(*line, general);
	*line = finale;
}

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


void	node_expander(char **command2, t_general *general)
{
	int		i;
	int		j;
	int		idx;
	int		flag;
	char	*dollar;

	i = -1;
	flag = 0;
	while (command2[++i])
	{
		if (general->flag_quotes[i] != 1)
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
			ft_expander_case(&command2[i], general);
		}
	}
	//free(dollar);
}

void	expander(t_general *general)
{
	t_lex	*tmp;

	tmp = general->lexer;
	while (tmp)
	{
		node_expander(tmp->command2, general);
		tmp = tmp->next;
	}
}
