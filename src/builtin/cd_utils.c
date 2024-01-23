/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:42:05 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/17 19:43:04 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_new_pwd(t_general *general)
{
	char	current_directory[PATH_MAX];
	char	*new_directory;

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	ft_printf("\nNEW_PWD=%s\n", current_directory);
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
	ft_printf("\nOLD_PWD = %s\n", old_directory);
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

int	ft_change_dir(char *new_dir, char **cmd2, t_general *general, char *old_dir)
{
	if (!cmd2[1])
	{
		if (chdir(new_dir) != 0)
		{
			printf("kitty shell: cd: %s\n", strerror(errno));
			return (0);
		}
	}
	else
	{
		if (chdir(new_dir) != 0)
		{
			printf("kitty shell: cd: %s: %s\n", cmd2[1], strerror(errno));
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
