/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/26 17:37:29 by jcardina         ###   ########.fr       */
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
				printf("wela zio non hai chiuso le '\n");
				g_last_exit_status = 1;
			}
		}
		else if (word[i] == '\"')
		{
			if ((ft_nb_quotes(word + i, '\"') % 2) == 0)
			{
				g_last_exit_status = 1;
				printf("wela zio non hai chiuso le '\n");
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
	while (path[i])
	{
		temppath = ft_strjoin(path[i], "/");
		if (!temppath)
		{
			perror("Errore nell'allocazione di memoria");
			exit(EXIT_FAILURE);
		}
		fullpath = ft_strjoin(temppath, command);
		free(temppath);
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
		printf("Il comando '%s' non è stato trovato\n", command);
	return (result);
}

int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;
	int		i;

	i = 0;
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
	tmp = pathfinder(node->command2[0],general->path); //ft_split(&general->envp2[my_setenv("$PATH", NULL, &general->envp2)][5], ':')
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
