/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:11:22 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/31 18:48:44 by jcardina         ###   ########.fr       */
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
			return ((char *)str);
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

char	*calcolate_parte_prima(char *input, char *posizione)
{
	char	*parte_prima;
	int		lunghezza_parte_prima;

	lunghezza_parte_prima = posizione - input;
	parte_prima = ft_substr(input, 0, lunghezza_parte_prima);
	return (parte_prima);
}

char	*calcolate_parte_dopo(char *fine_comando)
{
	char	*parte_dopo;
	int		lunghezza_parte_dopo;

	lunghezza_parte_dopo = strlen(fine_comando);
	parte_dopo = ft_substr(fine_comando, 0, lunghezza_parte_dopo);
	return (parte_dopo);
}

char	*find_fine_comando(char *posizione)
{
	char	*fine_comando;

	fine_comando = posizione + ft_strlen("$");
	while (*fine_comando != ' ' && *fine_comando != '\0'
		&& *fine_comando != '\"' && *fine_comando != '$'
		&& *fine_comando != '\'')
	{
		if (*fine_comando == '?')
			if (*fine_comando + 1 == '\0')
				return (fine_comando + 2);
		else
			return (fine_comando + 1);
		fine_comando++;
	}
	return (fine_comando);
}

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
