/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:51:44 by lmorelli          #+#    #+#             */
/*   Updated: 2023/12/14 16:17:54 by jcardina         ###   ########.fr       */
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
	while(str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

int my_setenv(char *name, char *value, char **environ)
{
	char	*env_var;
	//char	**matrixtmp;
	int		index;

	env_var = ft_strjoin(name, value);
	index = 0;
    // Cerca se la variabile d'ambiente esiste già
	while (environ[index] != NULL)
	{
		if (ft_strncmp(environ[index], name, ft_strlen(name)) == 0)
		{
			write(1, "AAA\n", 4);
			free(environ[index]);
			environ[index] = env_var; // Aggiorna il valore della variabile
			return 0;
		}
		index++;
	}

	// Se la variabile d'ambiente non esiste, aggiungila alla lista
	// gestire qui la memoria
	// environ[index] = env_var;
	// environ[index + 1] = NULL;
	matrixtmp = matrix_newline(environ, env_var);
	print_matrix(matrixtmp);
	free_matrix(environ);
	printf("---------------------%p\n", environ);
	environ = matrixtmp;
	envprint_matrix(matrixtmp);

	return 0; // Operazione completata con successo
}

// Funzione per gestire il comando export
void my_export(char *arg, char **env)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = ft_substr(arg, 0, uguallen(arg));
	if(uguallen(arg) != ft_strlen(arg))
		value = ft_substr(arg, uguallen(arg), ft_strlen(arg));
	if (name != NULL && value == NULL)
	{
		//funzione che modifica la matrice per bene;
		//fprintf(stderr, "Errore: formato non valido per export\n");
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
		print_export(general->enexp);
	while (node->command2[i]){
		my_export(node->command2[i], general->envp2);
		i++;
	}
}
