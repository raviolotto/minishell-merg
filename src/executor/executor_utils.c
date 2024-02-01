/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:54:45 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/01 17:56:20 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	builtinmanager(t_lex *node, t_general *general)
{
	if (node->builtin == 1)
		handle_echo(general, node);
	if (node->builtin == 2)
		handle_cd(general, node);
	if (node->builtin == 3)
		handle_pwd();
	if (node->builtin == 4)
		handle_export(general, node);
	if (node->builtin == 5)
		handle_unset(general, node);
	if (node->builtin == 6)
		handle_env(general);
	if (node->builtin == 7)
		handle_exit(node->command2, general);
}
