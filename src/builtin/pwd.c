/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:54:56 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/30 15:54:30 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	handle_pwd(void)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		ft_printf("%s\n", current_directory);
	else
	{
		g_last_exit_status = 1;
		ft_putstr_fd("kitty shell: error while getting current directory\n", 2);
	}
}
