/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:07:51 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/30 17:24:35 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

	// while (token[i])
	// {
	// 	res = ft_strjoin(res, "/");
	// 	res = ft_strjoin(res, token[i]);
	// 	i++;
	// }

char	*generate_res(char **args)
{
	int		i;
	char	**token;
	char	*res;

	token = ft_split(args[0], '/');
	i = 0;
	res = ft_strdup("/");
	while (token[i])
	{
		res = ft_strjoin(res, "/");
		res = ft_strjoin(res, token[i]);
		i++;
	}
	return (res);
}

void	wait_for_child_process(void)
{
	int		status;

	wait(&status);
	if (WIFEXITED(status))
	{
		g_last_exit_status = WEXITSTATUS(status);
		if (g_last_exit_status == 0)
			printf("\nsuccess = %d\n", g_last_exit_status);
		else
		{
			ft_putstr_fd("kitty shell: failure = ", 2);
			ft_putnbr_fd(g_last_exit_status, 2);
			ft_putstr_fd("\n", 2);
		}
	}
}

int	execute_external_command(char **args)
{
	pid_t	pid;
	char	*res;

	res = generate_res(args);
	if (access(res, X_OK) == 0)
	{
		pid = fork();
		if (pid < 0) 
		{
			g_last_exit_status = 1;
			ft_putstr_fd("kitty shell: error while forking\n", 2);
		}
		else if (pid == 0)
		{
			execve(res, args, NULL);
		}
		else
			wait_for_child_process();
		free(res);
		return (1);
	}
	free(res);
	return (0);
}
