/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:51:44 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/30 19:04:56 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	is_accepted_variable(char *var)
{
	int	i;

	i = 1;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	return (1);
}

int	uguallen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i - 1] == '+')
		i--;
	return (i);
}

int	my_setcontrol(char *environ, char *name, char *value)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strncmp(environ, name, len) == 0 && value && (environ[len] == '='
			|| environ[len] == '\0'))
		return (0);
	if (ft_strncmp(environ, name, len) == 0 && !value && (environ[len] == '='
			|| environ[len] == '\0'))
		return (1);
	return (-1);
}

void	env_append(char **env_var, char ***environ, char *value, int index)
{
	if (ft_strchr((*environ)[index], '=') == NULL)
		*env_var = ft_strjoin((*environ)[index], &value[1]);
	else
		*env_var = ft_strjoin((*environ)[index], &value[2]);
	return ;
}

int	my_setenv(char *name, char *value, char ***environ)
{
	char	*env_var;
	int		index;

	env_var = NULL;
	index = -1;
	while ((*environ)[++index] != NULL)
	{
		if (my_setcontrol((*environ)[index], name, value) == 0)
		{
			if (value[0] == '+')
				env_append(&env_var, environ, value, index);
			else
				env_var = ft_strjoin(name, value);
			free((*environ)[index]);
			(*environ)[index] = env_var;
			return (0);
		}
		if (my_setcontrol((*environ)[index], name, value) == 1)
			return (index);
	}
	if (!value)
		return (-1);
	env_var = ft_strjoin(name, ft_strchr(value, '='));
	*environ = matrix_newline(*environ, env_var);
	return (0);
}

void	show_export_error(char *arg)
{
	g_last_exit_status = 1;
	ft_putstr_fd("kitty shell:", 2);
	ft_putstr_fd(" export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	my_export(char *arg, char ***env, char ***enexp)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (is_accepted_variable(arg))
	{
		name = ft_substr(arg, 0, uguallen(arg));
		if (uguallen(arg) != ft_strlen(arg))
			value = ft_substr(arg, uguallen(arg), ft_strlen(arg));
		if (name != NULL && value == NULL)
		{
			if (my_setenv(name, value, enexp) == -1)
				*enexp = matrix_newline(*enexp, name);
			return ;
		}
		my_setenv(name, value, env);
		my_setenv(name, value, enexp);
	}
	else
		show_export_error(arg);
	free(name);
	free(value);
}

void	handle_export(t_general *general, t_lex *node)
{
	int	i;

	i = 1;
	if (node->command2[i] == NULL)
		print_export(general->enexp);
	while (node->command2[i])
	{
		my_export(node->command2[i], &(general->envp2), &(general->enexp));
		i++;
	}
}
