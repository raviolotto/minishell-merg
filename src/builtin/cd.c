#include "../../includes/mini_shell.h"
#include <errno.h>
#include <string.h>

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

int	ft_change_dir(char *new_dir, char **command2)
{
	if (!command2[1])
	{
		if (chdir(new_dir) != 0)
		{
			printf("kittyshell: cd: %s\n", strerror(errno));
			return (0);
		}
	}
	else
	{
		if (chdir(new_dir) != 0)
		{
			printf("kittyshell: cd: %s: %s\n", command2[1], strerror(errno));
			return (0);
		}
	}
	return (1);
}

int	ft_cd_only(char **env, char **command2)
{
	char	*home_dir;

	home_dir = ft_home_env(env);
	if (ft_change_dir(home_dir, command2) != 1)
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

	if (getcwd(current_directory, PATH_MAX) == NULL)
		return ;
	if (matrixlen(node->command2) > 2)
	{
		printf("kittyshell: cd: too many arguments\n");
		return ;
	}
	if (ft_cd_with_quotes(node->command2[1]) == 0)
	{
		printf("kittyshell: %s: No such file or directory\n", node->command2[1]);
		return ;
	}
	if (!node->command2[1])
	{
		if (ft_cd_only(general->envp2, node->command2) != 1)
			return ;
	}
	else
		if (ft_change_dir(node->command2[1], node->command2) != 1)
			return ;
}
