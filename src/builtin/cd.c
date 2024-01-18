/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:16:09 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/17 17:53:20 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	handle_cd(t_general *general, t_lex *node)
{
	char	current_directory[PATH_MAX];
	char	*old_directory;

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	if (matrixlen(node->command2) > 2)
	{
		printf("kitty shell: cd: too many arguments\n");
		return ;
	}
	if (ft_cd_with_quotes(node->command2[1]) == 0)
	{
		printf("kitty shell:%s:No such file or directory\n", node->command2[1]);
		return ;
	}
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
