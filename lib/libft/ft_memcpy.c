/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:44:00 by jcardina          #+#    #+#             */
/*   Updated: 2023/01/20 10:44:01 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	i = 0;
	if (!(void *) dst && !(void *) src)
		return (NULL);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned const char *) src;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return ((void *) dst);
}
