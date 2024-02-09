/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:15:36 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/09 16:47:06 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_supp_rm(char *str, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	ft_idx_quotes(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !c)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_nb_quotes(char *str, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str == 0)
		return (0);
	while (str[++i])
	{
		if (str[i] == c)
			ret ++;
	}
	return (ret);
}

int	ft_rm_quotes(char *str, int idx_double, t_general *general, int index)
{
	int	idx_single;

	idx_single = ft_idx_quotes(str, '\'');
	if (ft_nb_quotes(str, '\'') > 0 && ft_nb_quotes(str, '\"') == 0)
	{
		ft_supp_rm(str, '\'');
		general->flag_quotes[index] = 1;
	}
	else if (ft_nb_quotes(str, '\"') > 0 && ft_nb_quotes(str, '\'') == 0)
	{
		ft_supp_rm(str, '\"');
		general->flag_quotes[index] = 0;
	}
	else if (idx_double > idx_single)
	{
		ft_supp_rm(str, '\'');
		general->flag_quotes[index] = 1;
	}
	else if (idx_single > idx_double)
	{
		ft_supp_rm(str, '\"');
		general->flag_quotes[index] = 0;
	}
	return (1);
}

int	quotes_manager(char *str, t_general *general, int index)
{
	int	s_quote;
	int	d_quotes;
	int	all_quotes;
	int	idx_double;

	s_quote = ft_nb_quotes(str, '\'');
	d_quotes = ft_nb_quotes(str, '\"');
	all_quotes = s_quote + d_quotes;
	idx_double = ft_idx_quotes(str, '\"');
	if (all_quotes > 0)
		ft_rm_quotes(str, idx_double, general, index);
	else
		general->flag_quotes[index] = 0;
	return (1);
}
