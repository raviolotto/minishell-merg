/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:16:09 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/13 15:46:21 by frdal-sa         ###   ########.fr       */
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
}

// void ft_old_pwd(t_general *general)
// {
// 	char	current_directory[PATH_MAX];
// 	char	*old_directory;

// 	if (getcwd(current_directory, PATH_MAX) == NULL)
// 		return ;
// 	old_directory = ft_strjoin("=", current_directory);
// 	my_setenv("OLDPWD", old_directory, &(general->envp2));
// 	ft_printf("\nOLD_PWD = %s\n", old_directory);
// }

void ft_old_pwd(t_general *general, char *old_dir)
{
	char	*old_directory;

	old_directory = ft_strjoin("=", old_dir);
	my_setenv("OLDPWD", old_directory, &(general->envp2));
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

int	ft_change_dir(char *new_dir, char **command2, t_general *general, char *old_dir)
{
	if (!command2[1])
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
			printf("something went wrong, impossible to change directory\n");
			printf("kitty shell: cd: %s: %s\n", command2[1], strerror(errno));
			return (0);
		} else {
			printf("successfull change directory\n");
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

void	handle_cd(t_general *general, t_lex *node)
{
	char	current_directory[PATH_MAX];
	char 	*old_directory;

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	if (matrixlen(node->command2) > 2)
	{
		printf("kitty shell: cd: too many arguments\n");
		return ;
	}
	if (ft_cd_with_quotes(node->command2[1]) == 0)
	{
		printf("kitty shell: %s: No such file or directory\n", node->command2[1]);
		return ;
	}

	//store old pwd and assign later only if successfull
	old_directory = ft_strjoin("=", current_directory);
	
	if (!node->command2[1])
	{
		if (ft_cd_only(general->envp2, node->command2, general, old_directory) != 1)
			return ;
	}
	else
		if (ft_change_dir(node->command2[1], node->command2, general, old_directory) != 1)
			return ;
}
