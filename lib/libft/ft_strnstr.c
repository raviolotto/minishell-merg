/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:10:03 by jcardina          #+#    #+#             */
/*   Updated: 2023/03/09 12:10:05 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*lit || lit == NULL)
		return ((char *) big);
	if (!n)
		return (0);
	i = 0;
	while (i < n && big[i])
	{
		j = 0;
		while (big[i + j] == lit[j] && (i + j) < n)
		{
			if (lit[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
