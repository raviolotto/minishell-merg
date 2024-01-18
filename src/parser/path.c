/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/18 18:25:11 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void handle_quotes(char *word)
{
	int	i;

	i = 0;
	while(word[i] != '\0')
	{
		if(word[i] == '\'')
			{
				if ((ft_nb_quotes(word + i, '\'') % 2) == 0)
					{
						printf("errore 1");
						g_last_exit_status = 1;
						return;
					}
				return;
			}
		else if (word[i] == '\"')
			{
				if ((ft_nb_quotes(word + i, '\"') % 2) == 0)
					{
						printf("errore 2");
						g_last_exit_status = 1;
						return;
					}
				return;
			}
		i++;	
	}
	return;
}

// void handle_quotes(char *word)
// {
// 	size_t	len;
// 	int		num_quotes;

// 	len = ft_strlen(word);
// 	num_quotes = 0;

// 	// Check if the argument is enclosed in single or double quotes
// 	if (len >= 2 &&
// 		((word[0] == '\'' && word[len - 1] == '\'') || (word[0] == '\"' && word[len - 1] == '\"')))
// 	{
// 		// Check for matching quotes at the beginning and end
// 		if (word[0] != word[len - 1])
// 		{
// 			printf("1Error: Unterminated quotes within the word '%s'.\n", word);
// 			// Handle the error as needed
// 			g_last_exit_status = 1;
// 			return; // Return an empty string to indicate an error
// 		}
// 		// Remove the quotes and return the substring
// 		//return;
// 	}
// 	// Check for unterminated single quotes at the beginning
// 	if (word[0] == '\'' && word[len - 1] != '\'')
// 	{
// 		printf("2Error: Unterminated single quote within the word '%s'.\n", word);
// 		// Handle the error as needed
// 		g_last_exit_status = 1;
// 		return; // Return an empty string to indicate an error
// 	}
// 	// Check for unterminated double quotes at the beginning
// 	if (word[0] == '\"' && word[len - 1] != '\"')
// 	{
// 		printf("3Error: Unterminated double quote within the word '%s'.\n", word);
// 		// Handle the error as needed
// 		g_last_exit_status = 1;
// 		return; // Return an empty string to indicate an error
// 	}
// 	// Check for quotes at the end without matching at the beginning
// 	if ((word[0] != '\'' && word[0] != '\"') && (word[len - 1] == '\'' || word[len - 1] == '\"'))
// 	{
// 		printf("4Error: Unmatched quotes at the end within the word '%s'.\n", word);
// 		// Handle the error as needed
// 		g_last_exit_status = 1;
// 		return; // Return an empty string to indicate an error
// 	}
// 	// Count the number of quotes within the word
// 	for (size_t i = 0; i < len; i++)
// 	{
// 		if (word[i] == '\'' || word[i] == '\"')
// 			num_quotes++;
// 	}
// 	// Check if the total number of quotes is even
// 	if (num_quotes % 2 != 0)
// 	{
// 		printf("5Error: Unmatched quotes within the word '%s'.\n", word);
// 		// Handle the error as needed
// 		g_last_exit_status = 1;
// 		return; // Return an empty string to indicate an error
// 	}
// 	// If no quotes are found, return the word
// 	return;
// }

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
	int i = 1;

	node->command2 = maxxisplit (str, ' ');
	while(i < matrixlen(node->command2))
	{
		//if fuzione delle quotes ok
				handle_quotes(node->command2[i]);
				ft_cd_with_quotes(node->command2[i]);
			i++;
	}
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
