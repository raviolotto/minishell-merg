#include "../../includes/mini_shell.h"
#include <errno.h>
#include <string.h>

void	ft_remove_char_in_str(char *str, char c)
{
	int	len;
	int	i;
	int	j;

	len = strlen(str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	ft_find_char_index_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !c)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_count_char(char *str, char c)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (str == 0)
		return (0);
	while (str[++i])
	{
		if (str[i] == c)
			ret ++;
	}
	return (ret);
}

int	ft_remove_quotes(char *arg, int n_single_quote, int n_double_quotes,
	int index_double_quotes)
{
	int	index_single_quote;

	index_single_quote = ft_find_char_index_str(arg, '\'');
	if (n_single_quote > 0 && n_double_quotes == 0)
	{
		ft_remove_char_in_str(arg, '\'');
		return (1);
	}
	if (n_double_quotes > 0 && n_single_quote == 0)
	{
		ft_remove_char_in_str(arg, '\"');
		return (1);
	}
	if (index_single_quote > index_double_quotes)
	{
		ft_remove_char_in_str(arg, '\"');
		return (-1);
	}
	if (index_double_quotes > index_single_quote)
	{
		ft_remove_char_in_str(arg, '\'');
		return (-1);
	}
	return (1);
}

int	ft_cd_check_quotes(char *arg)
{
	int	n_single_quote;
	int	n_double_quotes;
	int	total_quotes;
	int	index_double_quotes;
	int	result;

	n_single_quote = ft_count_char(arg, '\'');
	n_double_quotes = ft_count_char(arg, '\"');
	total_quotes = n_single_quote + n_double_quotes;
	index_double_quotes = ft_find_char_index_str(arg, '\"');
	if (total_quotes > 0)
	{
		result = ft_remove_quotes(arg, n_single_quote, n_double_quotes,
				index_double_quotes);
		if (result == 1)
			return (1);
		else if (result == -1)
			return (-1);
	}
	return (1);
}

// int	ft_cd_with_quotes(t_lex *node)
// {
// 	if ((node->command[1][0] == "\'" || node->command[1][0] == "\"") && (node->command[1][ft_strlen(node->command[1])]) == "\'" || node->command[1][0] == "\"" && (node->command[1][ft_strlen(node->command[1])]))
// }

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
			return (-1);
		}
	}
	else
	{
		if (chdir(new_dir) != 0)
		{
			printf("kittyshell: cd: %s: %s\n", command2[1], strerror(errno));
			return (-1);
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
		return (-1);
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
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (ft_cd_check_quotes(node->command2[1]) == -1)
	{
		printf("minishell: %s: No such file or directory\n", node->command2[1]);
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
