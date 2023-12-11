/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:06:28 by jcardina          #+#    #+#             */
/*   Updated: 2023/03/09 12:06:31 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_lenght(long nb)
{
	size_t	count;

	count = 0;
	if (nb <= 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	c;
	long	nbr;

	nbr = n;
	c = ft_lenght(nbr);
	result = (char *)malloc(c + 1);
	if (!result)
		return (NULL);
	result[c--] = '\0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		result[c] = 48 + (nbr % 10);
		nbr = nbr / 10;
		c--;
	}
	if (nbr >= 0 && nbr < 10)
		result[c] = 48 + nbr;
	return (result);
}
