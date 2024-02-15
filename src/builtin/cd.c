/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:16:09 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
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
	if (!node->arguments[1])
	{
		if (ft_cd_only(general->environment_variables, node->arguments, general,
				old_directory) != 1)
			return ;
	}
	else if (ft_change_dir(node->arguments[1], node->arguments, general,
			old_directory) != 1)
		return ;
}
