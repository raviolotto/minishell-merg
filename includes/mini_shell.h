/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:31:51 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/16 19:10:26 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

extern int	g_last_exit_status;

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h>  // For PATH_MAX
# include <errno.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "structure.h"
# include "parser.h"
# include "visual.h"
# include "utils.h"
# include "builtin.h"
# include "executor.h"
//# include "global.h"

#endif

//se metto una sola pipe il pipe status é due dovrebbe essere 0
