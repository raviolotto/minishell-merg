/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:28:02 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/17 17:56:44 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*pathfinder(char *command, char **path)
{
	char	*result;
	int		i;
	char	*fullpath;
	char	*temp_path;

	i = 0;
	result = NULL;
	while (path[i])
	{
		temp_path = ft_strjoin(path[i], "/");
		if (!temp_path)
		{
			perror("Errore nell'allocazione di memoria");
			exit(EXIT_FAILURE);
		}
		fullpath = ft_strjoin(temp_path, command);
		free(temp_path);
		if (!fullpath)
		{
			perror("Errore nell'allocazione di memoria");
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
		printf("Il comando '%s' non è stato trovato nei percorsi specificati.\n", command);//da scrivere in inglese
	// std 1.ERROR, 2. input ed 3. output? le precedenti task sonon gia´ state eseguite?
	return (result);
}

int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;

	node->command2 = maxxisplit(str, ' ');
	node->builtin = dumb_builtin_check(node->command2[0]);
	if (node->builtin != 0)
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
		tmp = tmp->next;
	}
	return (0);
}

