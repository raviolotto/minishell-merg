/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:14:30 by jcardina          #+#    #+#             */
/*   Updated: 2023/04/04 17:00:39 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_strlen_pf(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr_pf(char *str)
{
	int	i;

	if (str == NULL)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	i = -1;
	while (str[++i])
		ft_putchar_pf(str[i]);
	i = ft_strlen_pf(str);
	return (i);
}
