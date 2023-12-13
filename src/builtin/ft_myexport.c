/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:51:44 by lmorelli          #+#    #+#             */
/*   Updated: 2023/12/13 17:01:40 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

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
	while(str[i] != '=')
		i++;
	return (i);
}

int my_setenv(char *name, char *value, char **environ)
{
	char	*env_var;
	int		index;

	env_var = ft_strjoin(name, value);
	index = 0;
    // Cerca se la variabile d'ambiente esiste già
	while (environ[index] != NULL)
	{
		if (ft_strncmp(environ[index], name, ft_strlen(name)) == 0)
		{
			write(1, "AAA\n", 4);
			environ[index] = env_var; // Aggiorna il valore della variabile
			return 0;
		}
		index++;
	}

	// Se la variabile d'ambiente non esiste, aggiungila alla lista
	environ[index] = env_var;
	environ[index + 1] = NULL;

	return 0; // Operazione completata con successo
}

// Funzione per gestire il comando export
void my_export(char *arg, char **env)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, uguallen(arg));
	value = ft_substr(arg, uguallen(arg), ft_strlen(arg));

	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Errore: formato non valido per export\n");
		return;
	}

	if (my_setenv(name, value, env) != 0)
		fprintf(stderr, "Errore nell'impostare la variabile d'ambiente\n");
	free(name);
	free(value);
}

void	handle_export(t_general *general, t_lex *node)
{
	int	i;

	i = 1;
	if	(node->command2[i] == NULL)
		print_export(general->envp2);
	while (node->command2[i]){
		my_export(node->command2[i], general->envp2);
		i++;
	}
}
