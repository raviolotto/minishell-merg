/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:13:40 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/31 14:13:44 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_new_pwd(t_general *general)
{
	char	current_directory[PATH_MAX];
	char	*new_directory;

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	new_directory = ft_strjoin("=", current_directory);
	my_setenv("PWD", new_directory, &(general->envp2));
	my_setenv("PWD", new_directory, &(general->enexp));
}

void	ft_old_pwd(t_general *general, char *old_dir)
{
	char	*old_directory;

	old_directory = ft_strjoin("=", old_dir);
	my_setenv("OLDPWD", old_directory, &(general->envp2));
	my_setenv("OLDPWD", old_directory, &(general->enexp));
}

char	*ft_home_env(char **env)
{
	char	*home_dir;
	int		i;

	home_dir = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("HOME=", env[i], 5) == 0)
		{
			home_dir = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			break ;
		}
		i++;
	}
	return (home_dir);
}

void	show_cd_error(char *cmd2, char *error)
{
	g_last_exit_status = 1;
	ft_putstr_fd("kitty shell: cd: ", 2);
	ft_putstr_fd(cmd2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_change_dir(char *new_dir, char **cmd2, t_general *general, char *old_dir)
{
	if (!cmd2[1])
	{
		if (chdir(new_dir) != 0)
		{
			show_cd_error(cmd2[1], strerror(errno));
			return (0);
		}
	}
	else
	{
		if (chdir(new_dir) != 0)
		{
			show_cd_error(cmd2[1], strerror(errno));
			return (0);
		}
		else
		{
			ft_old_pwd(general, old_dir);
			ft_new_pwd(general);
			return (1);
		}
	}
	return (1);
}

int	ft_cd_only(char **env, char **command2, t_general *general, char *old_dir)
{
	char	*home_dir;

	home_dir = ft_home_env(env);
	if (ft_change_dir(home_dir, command2, general, old_dir) != 1)
	{
		free(home_dir);
		return (0);
	}
	free(home_dir);
	return (1);
}
