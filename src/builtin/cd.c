/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:16:09 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/25 18:13:35 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	handle_cd(t_general *general, t_lex *node)
{
	char	current_directory[PATH_MAX];
	char	*old_directory;

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	old_directory = current_directory;
	if (!node->command2[1])
	{
		if (ft_cd_only(general->envp2, node->command2, general,
				old_directory) != 1)
			return ;
	}
	else if (ft_change_dir(node->command2[1], node->command2, general,
			old_directory) != 1)
		return ;
}
