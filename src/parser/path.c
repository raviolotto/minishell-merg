/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/16 20:13:27 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:45:46 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/16 19:51:19 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char *handle_quotes(char *word)
{
    size_t len;
	
	len = ft_strlen(word);

    // Check if the argument is enclosed in single or double quotes
    if (len >= 2 &&
        ((word[0] == '\'' && word[len - 1] == '\'') || (word[0] == '\"' && word[len - 1] == '\"')))
    {
        // Check for matching quotes at the beginning and end
        if (word[0] != word[len - 1])
        {
            printf("Error: Unterminated quotes within the word '%s'.\n", word);
            // Handle the error as needed
            return ft_strdup(""); // Return an empty string to indicate an error
        }

        // Remove the quotes and return the substring
        return ft_substr(word, 1, len - 2);
    }

    // Check for unterminated single quotes
    if (word[0] == '\'' && word[len - 1] != '\'')
    {
        printf("Error: Unterminated single quote within the word '%s'.\n", word);
        // Handle the error as needed
        return ft_strdup(""); // Return an empty string to indicate an error
    }

    // Check for unterminated double quotes
    if (word[0] == '\"' && word[len - 1] != '\"')
    {
        printf("Error: Unterminated double quote within the word '%s'.\n", word);
        // Handle the error as needed
        return ft_strdup(""); // Return an empty string to indicate an error
    }

    // If no quotes are found, return the word
    return ft_strdup(word);
}


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


int build_matrix(char *str, t_lex *node, t_general *general)
{
    char *tmp;
	int i;
	i = 0;
	
    node->command2 = maxxisplit(str, ' ');
    node->builtin = dumb_builtin_check(node->command2[0]);
    if (node->builtin != 0)
        return (0);

    
    while (node->command2[i] != NULL)
    {
        // Handle quotes for each word (token) in the command
        char *quoted_word = handle_quotes(node->command2[i]);
        if (quoted_word == NULL)
        {
            // Error handling: free allocated memory and return
            int j = 0;
            while (node->command2[j] != NULL)
                free(node->command2[j++]);
            free(node->command2);
            return 1;
        }

        // Replace the original word with the quoted version
        free(node->command2[i]);
        node->command2[i] = quoted_word;

        i++;
    }

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

