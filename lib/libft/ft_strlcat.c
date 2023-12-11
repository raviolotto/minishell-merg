/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:09:43 by jcardina          #+#    #+#             */
/*   Updated: 2023/03/09 12:09:45 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src && !dst)
		return (0);
	if (destsize == 0)
		return (ft_strlen(src));
	while (dst[j] && j < destsize)
		j++;
	while ((i + j + 1) < destsize && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j != destsize)
		dst[j + i] = '\0';
	return (j + (ft_strlen(src)));
}
