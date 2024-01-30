/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/01/30 16:31:51 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/mini_shell.h"

void	handle_quotes(char *word)
{
	int	i;

	i = -1;
	while (word[++i] != '\0')
	{
		if (word[i] == '\'')
		{
			if ((ft_nb_quotes(word + i, '\'') % 2) == 0)
			{
				g_last_exit_status = 1;
				ft_putstr_fd("kitty shell: you didn't close the \'\n", 2);
			}
		}
		else if (word[i] == '\"')
		{
			if ((ft_nb_quotes(word + i, '\"') % 2) == 0)
			{
				g_last_exit_status = 1;
				ft_putstr_fd("kitty shell: you didn't close the \"\n", 2);
			}
			return ;
		}
	}
	return ;
}

char	*pathfinder(char *command, char **path)
{
	char	*result;
	int		i;
	char	*fullpath;
	char	*temppath;

	i = 0;
	result = NULL;

	if (path == NULL)
	{
		g_last_exit_status = 127;
		ft_putstr_fd("kitty shell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found \n", 2);
		return (result);
	}
	while (path[i])
	{
		temppath = ft_strjoin(path[i], "/");
		if (!temppath)
		{
			g_last_exit_status = 1;
			ft_putstr_fd("Error in memory allocation /n", 2);
			exit(EXIT_FAILURE);
		}
		fullpath = ft_strjoin(temppath, command);
		free(temppath);
		if (!fullpath)
		{
			g_last_exit_status = 1;
			ft_putstr_fd("Error in memory allocation /n", 2);
			exit(EXIT_FAILURE);
		}
		if (access(fullpath, F_OK | X_OK) == 0)
		{
			result = fullpath;
			break ;
		}
		free(fullpath);
		i++;
	}
	if (result == NULL) 
	{
		g_last_exit_status = 127;
		ft_putstr_fd("kitty shell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found \n", 2);
	}

	return (result);
}

void	pathpiker(t_general *general)
{
	int index;

	index = my_setenv("PATH", NULL, &general->envp2);
	if (index == -1)
	{
		if(general->path != NULL)
			free_matrix(general->path);
		general->path = NULL;
		return ;
	}
	general->path = ft_split((general->envp2[index] + 5), ':');
}

int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;
	int		i;

	i = 0;

	pathpiker(general);
	node->command2 = maxxisplit (str, ' ');
	while (i < matrixlen(node->command2))
	{
		handle_quotes(node->command2[i]);
		ft_cd_with_quotes(node->command2[i], general, i);
		i++;
	}
	node->builtin = dumb_builtin_check(node->command2[0]);
	if (node->builtin != 0)
		return (0);
	tmp = pathfinder(node->command2[0],general->path);
	if (tmp != NULL)
	{
		free(node->command2[0]);
		node->command2[0] = tmp;
	}
	return (0);
}

int	list_commander(t_general *general)
{
	t_lex	*tmp;

	tmp = general->lexer;
	while (tmp)
	{
		if (tmp->token == 0)
			build_matrix(tmp->command, tmp, general);
		tmp = tmp->next;
	}
	return (0);
}
