/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:44:54 by jcardina          #+#    #+#             */
/*   Updated: 2023/01/20 10:44:55 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = NULL;
	tmp = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		tmp[i] = (unsigned char) c;
		i++;
	}
	return ((void *) b);
}
