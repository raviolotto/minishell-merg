/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:05:57 by jcardina          #+#    #+#             */
/*   Updated: 2023/03/09 12:06:00 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *) s;
	if (n == 0)
		return ;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
	return ;
}
