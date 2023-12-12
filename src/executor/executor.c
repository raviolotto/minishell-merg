/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2023/12/12 19:08:00 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void    builtinmanager(t_lex *node, t_general *general)
{
    // if (node->builtin == 1)
    //     handle_echo
    // if (node->builtin == 2)
	// 	handle_cd();
    if (node->builtin == 3)
        handle_pwd();
    if (node->builtin == 4)
        handle_export(general, node);
    // if (node->builtin == 5)
    //     //handle_unset
    if (node->builtin == 6)
        handle_env(general);
    // if (node->builtin == 7)
    //     handle_exit
    
}

void    executor(t_general *general)
{
	t_lex	*tmp;
	tmp = general->lexer;
	while (tmp)
	{
		if(tmp->builtin > 0)
			builtinmanager(tmp, general);
		else
        {
			execute_external_command(tmp->command2);
            wait(NULL);
        }
        tmp = tmp->next;
	}
}