/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:16:28 by jcardina          #+#    #+#             */
/*   Updated: 2023/04/04 17:00:03 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_putchar_pf(char c);
int		ft_putstr_pf(char *str);
int		ft_strlen_pf(char *str);
void	ft_format(va_list args, const char c, int *nchar);
int		ft_exa_pf(unsigned int nb, const char format, int i);
int		ft_putnbr_pf(int nb, int i);
int		ft_putnbr_un_pf(unsigned int nb, int i);
int		ft_putptr_pf(unsigned long long ptr, int i);

#endif
