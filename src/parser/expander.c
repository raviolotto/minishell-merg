/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:11:22 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/08 18:28:42 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*sostituisci_comando_dollaro(char *input, t_general *general)
{
	char	*fine_comando;
	char	*comando;
	char	*updated_input;
	char	*parte_prima;
	char	*second_part;

	while (1)
	{
		if (ft_strchr(input, '$') == NULL)
			break ;
		fine_comando = find_fine_comando(ft_strchr(input, '$'));
		comando = ft_substr(ft_strchr(input, '$'), 0,
				fine_comando - ft_strchr(input, '$'));
		updated_input = ft_strjoin(calcolate_parte_prima(&parte_prima, input,
					ft_strchr(input, '$')),
				find_sostituzione(comando, general));
		updated_input = ft_strjoin2(updated_input,
				calcolate_parte_dopo(&second_part, fine_comando));
		free(comando);
		free(parte_prima);
		free(second_part);
		free(input);
		return (sostituisci_comando_dollaro(updated_input, general));
	}
	return (input);
}

void	ft_expander_case(char **line, t_general *general)
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

	i = -1;
	while (command2[++i])
	{
		if (general->flag_quotes[i] != 1)
		{
			ft_expander_case(&command2[i], general);
		}
	}
}

void	expander(t_general *general)
{
	t_lex	*tmp;

	tmp = general->lexer;
	while (tmp)
	{
		if (tmp->token == 0)
			node_expander(tmp->command2, general);
		tmp = tmp->next;
	}
}
