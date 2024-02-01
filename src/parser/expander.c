/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:11:22 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 17:35:26 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

//da controllare le allocazioni di memoria vegono liberate
char	*sostituisci_comando_dollaro(char *input, t_general *general)
{
	char	*posizione;
	char	*fine_comando;
	char	*comando;
	char	*updated_input;

	posizione = input;
	while (1)
	{
		posizione = find_substring_position(posizione, "$");
		if (posizione == NULL)
			break ;
		fine_comando = find_fine_comando(posizione);
		comando = ft_substr(posizione, 0, fine_comando - posizione);
		updated_input = ft_strjoin(calcolate_parte_prima(input, posizione),
				find_sostituzione(comando, general));
		updated_input = ft_strjoin(updated_input,
				calcolate_parte_dopo(fine_comando));
		free(comando);
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
