/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:25:59 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*find_executable_path(char *command, char **path, char *result)
{
	int		i;
	char	*fullpath;
	char	*temppath;

	i = 0;
	while (path[i])
	{
		temppath = ft_strjoin(path[i], "/");
		if (!temppath)
			manage_memory_error();
		fullpath = ft_strjoin(temppath, command);
		free(temppath);
		if (!fullpath)
			manage_memory_error();
		if (access(fullpath, F_OK | X_OK) == 0)
		{
			result = fullpath;
			break ;
		}
		free(fullpath);
		i++;
	}
	return (result);
}

char	*pathfinder(char *command, char **path)
{
	char	*result;

	result = NULL;
	if (path == NULL)
	{
		show_pathfinder_error(command);
		return (result);
	}
	result = find_executable_path(command, path, result);
	if (result == NULL)
	{
		show_pathfinder_error(command);
		return (result);
	}
	return (result);
}

void	pathpiker(t_general *general)
{
	int	index;

	index = my_setenv("PATH", NULL, &general->environment_variables);
	if (index == -1)
	{
		if (general->path != NULL)
			free_matrix(general->path);
		general->path = NULL;
		return ;
	}
	if (general->path != NULL)
		free_matrix(general->path);
	general->path = ft_split((general->environment_variables[index] + 5), ':');
}

int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;
	int		i;

	i = 0;
	pathpiker(general);
	node->arguments = maxxisplit (str, ' ');
	while (i < matrixlen(node->arguments))
	{
		if (handle_quotes(node->arguments[i]) == 1)
			return (1);
		quotes_manager(node->arguments[i], general, i);
		i++;
	}
	node->builtin = dumb_builtin_check(node->arguments[0]);
	if (node->builtin != 0)
		return (0);
	if (access(node->arguments[0], F_OK | X_OK) == 0)
		return (0);
	tmp = pathfinder(node->arguments[0], general->path);
	if (tmp != NULL)
	{
		free(node->arguments[0]);
		node->arguments[0] = tmp;
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
			build_matrix(tmp->main_command, tmp, general);
		else if (tmp->token != 0 && tmp->token != 1)
			file_name_handler(tmp);
		tmp = tmp->next;
	}
	return (0);
}
