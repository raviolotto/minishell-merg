/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:25:59 by frdal-sa          #+#    #+#             */
/*   Updated: 2024/02/09 21:27:18 by jcardina         ###   ########.fr       */
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

	index = my_setenv("PATH", NULL, &general->envp2);
	if (index == -1)
	{
		if (general->path != NULL)
			free_matrix(general->path);
		general->path = NULL;
		return ;
	}
	if (general->path != NULL)
		free_matrix(general->path);
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
		if (handle_quotes(node->command2[i]) == 1)
			return (1);
		quotes_manager(node->command2[i], general, i);
		i++;
	}
	node->builtin = dumb_builtin_check(node->command2[0]);
	if (node->builtin != 0)
		return (0);
	if (access(node->command2[0], F_OK | X_OK) == 0)
		return (0);
	tmp = pathfinder(node->command2[0], general->path);
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
		else if (tmp->token != 0 && tmp->token != 1)
			file_name_handler(tmp);
		tmp = tmp->next;
	}
	return (0);
}
