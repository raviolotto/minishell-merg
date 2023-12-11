/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/11 19:14:14 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char *pathfinder(char *command, char **path)
{
	char *result = NULL;
	int i = 0;

	while (path[i] != NULL)
	{
		char *tempPath = ft_strjoin(path[i], "/");
		if (!tempPath) {
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }

        char *fullPath = ft_strjoin(tempPath, command);
        free(tempPath);

        if (!fullPath) {
            perror("Errore nell'allocazione di memoria");
            exit(EXIT_FAILURE);
        }

        if (access(fullPath, F_OK | X_OK) == 0) {
            result = fullPath;
            break;
        }
		free(fullPath);
		i++;
	}
	if (result == NULL)
	{
		fprintf(stderr, "Il comando '%s' non è stato trovato nei percorsi specificati.\n", command);
		result = "";
	}
	return (result);
}
int	build_matrix(char *str, t_lex *node, t_general *general)
{
	char	*tmp;

	node->command2 = ft_split(str, ' ');
	node->builtin = dumb_buildin_check(node->command2[0]);
	if (node->builtin != 0)
		return(0);
	tmp = pathfinder(node->command2[0], general->path);
	free(node->command2[0]);
	node->command2[0] = tmp;
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
}
