/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/09 16:36:16 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char *pathfinder(char *command, char **path)
{
	char *result;
	int	i;
	char *fullPath;
	char *tempPath;

	i = 0;
	result = NULL;
	while (path[i])
	{
		tempPath = ft_strjoin(path[i], "/");
		if (!tempPath)
		{
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }
        fullPath = ft_strjoin(tempPath, command);
        free(tempPath);
        if (!fullPath)
		{
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }
        if (access(fullPath, F_OK | X_OK) == 0)
		{
            result = fullPath;
            break;
        }
		free(fullPath);
		i++;
	}
	if (result == NULL)
		printf("Il comando '%s' non è stato trovato nei percorsi specificati.\n", command); // std 1.ERROR, 2. input ed 3. output? le precedenti task sonon gia´ state eseguite?
	return (result);
}
int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;

	node->command2 = ft_split(str, ' ');
	node->builtin = dumb_builtin_check(node->command2[0]);
	if (node->builtin != 0)
		return(0);
	tmp = pathfinder(node->command2[0], general->path);
	if(tmp != NULL)
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
	while(tmp)
	{
		if(tmp->token == 0)
			build_matrix(tmp->command, tmp, general);
		tmp = tmp->next;
	}
	return (0);
}
