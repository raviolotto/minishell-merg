/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:41:24 by jcardina          #+#    #+#             */
/*   Updated: 2023/04/04 17:01:28 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_pf(unsigned long long ptr, int i)
{
	if (ptr >= 16)
	{
		i++;
		i = ft_putptr_pf(ptr / 16, i);
	}
	ft_putchar_pf("0123456789abcdef"[ptr % 16]);
	return (i);
}
