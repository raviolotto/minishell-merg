/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:11:22 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/09 16:36:00 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*replace_dollar_command(char *input, t_general *general)
{
	char	*end_command;
	char	*command;
	char	*updated_input;
	char	*first_part;
	char	*second_part;

	while (1)
	{
		if (ft_strchr(input, '$') == NULL)
			break ;
		end_command = find_end_command(ft_strchr(input, '$'));
		command = ft_substr(ft_strchr(input, '$'), 0,
				end_command - ft_strchr(input, '$'));
		updated_input = ft_strjoin(calculate_first_part(&first_part, input,
					ft_strchr(input, '$')),
				find_substitution(command, general));
		updated_input = ft_strjoin2(updated_input,
				calculate_final_part(&second_part, end_command));
		free(command);
		free(first_part);
		free(second_part);
		free(input);
		return (replace_dollar_command(updated_input, general));
	}
	return (input);
}

void	ft_expander_case(char **line, t_general *general)
{
	char	*end;

	end = replace_dollar_command(*line, general);
	*line = end;
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
