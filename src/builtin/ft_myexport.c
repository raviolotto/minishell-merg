/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:51:44 by lmorelli          #+#    #+#             */
/*   Updated: 2023/12/18 18:11:48 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int is_accepted_variable(char *var)
{
	int i = 1;
	
	if (!ft_isalpha(var[0]) && var[0] != '_')
        return (0);
	while(var[i] != '=' && var[i] != '+')
	{
        if (!ft_isalpha(var[i]) && var[i] != '_')
            	return (0);
        i++;
    }
    return (1);
}

void	print_export(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return;
	while(matrix[i] != NULL)
	{
		printf("declare -x %s\n", matrix[i]);
		i++;
	}
	return;
}

int	uguallen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '=' && str[i] != '\0')
		i++;
	if(str[i - 1] == '+')
		i--;
	return (i);
}
int my_setcontrol(char *environ, char *name, char *value)
{
	int	len;

	len = ft_strlen(name);
	if(ft_strncmp(environ, name, len) == 0 && value && environ[len + 1] == '=')
		return (0);
	if(ft_strncmp(environ, name, len) == 0 && !value && environ[len + 1] == '=')
		return (1);
}

int my_setenv(char *name, char *value, char ***environ)
{
	char	*env_var;
	int		index;

	env_var = NULL;
	index = -1;
	while ((*environ)[++index] != NULL)
	{
		if (ft_strncmp((*environ)[index], name, ft_strlen(name)) == 0 && value)
		{
			if (value[0] == '+')
				env_var = ft_strjoin((*environ)[index], &value[2]);
			else
				env_var = ft_strjoin(name, value);
			free((*environ)[index]);
			(*environ)[index] = env_var; // Aggiorna il valore della variabile
			return 0;
		}
		if (ft_strncmp((*environ)[index], name, ft_strlen(name)) == 0 && !value)
			return (index);
	}
	if (!value)
		return(-1);
	env_var = ft_strjoin(name, ft_strchr(value, '='));
	*environ = matrix_newline(*environ, env_var);
	return 0;
}

// Funzione per gestire il comando export
void my_export(char *arg, char ***env, char ***enexp)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if(is_accepted_variable(arg))
	{	
	name = ft_substr(arg, 0, uguallen(arg));
	if(uguallen(arg) != ft_strlen(arg))
		value = ft_substr(arg, uguallen(arg), ft_strlen(arg));
	if (name != NULL && value == NULL)
	{
		if(my_setenv(name, value, enexp) == -1)
			*enexp = matrix_newline(*enexp, name);
		return;
	}
	my_setenv(name, value, env);
	my_setenv(name, value, enexp);}
	else
		printf("bash: export: `%s': not a valid identifier\n", arg);
	free(name);
	free(value);
}

void	handle_export(t_general *general, t_lex *node)
{
	int	i;

	i = 1;
	if	(node->command2[i] == NULL)
		print_export(general->enexp);
	while (node->command2[i]){
		my_export(node->command2[i], &(general->envp2), &(general->enexp));
		i++;
	}
}
