/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:51:44 by lmorelli          #+#    #+#             */
/*   Updated: 2023/12/12 20:31:21 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	uguallen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '=')
		i++;
	return (i);
}

int my_setenv(const char *name, const char *value, char **environ)
{
    size_t len = strlen(name) + strlen(value) + 1; // +2 per '=' e '\0'
    char *env_var = (char *)malloc(len);
    if (env_var == NULL) {
        perror("Errore di allocazione di memoria");
        return -1;
    }
    snprintf(env_var, len, "%s%s", name, value);

    // Cerca se la variabile d'ambiente esiste già
    int index = 0;
    while (environ[index] != NULL) {
        char *env_name = strtok(environ[index], "=");
        if (env_name && strcmp(env_name, name) == 0)
        {
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

    // char *arg_copy = strdup(arg);
    // if (arg_copy == NULL) {
    //     fprintf(stderr, "Errore nell'allocazione della memoria\n");
    //     return;
    // }

    // char *name = strtok(arg_copy, "=");
    // char *value = strtok(NULL, "");
	printf ("args = %s\n", arg);
	name = ft_substr(arg, 0, uguallen(arg));
	printf("name = %s\n", name);
	value = ft_substr(arg, uguallen(arg), ft_strlen(arg));
	printf("value = %s\n", value);

	if (name == NULL || value == NULL) {
		fprintf(stderr, "Errore: formato non valido per export\n");
		//free(arg_copy);
		return;
	}

	if (my_setenv(name, value, env) != 0) {
		fprintf(stderr, "Errore nell'impostare la variabile d'ambiente\n");
	}

	//free(arg_copy);
}

void	handle_export(t_general *general, t_lex *node)
{
	int	i;

	i = 0;
	write(1, "a\n", 2);
	while (node->command2[i]){
		my_export(node->command2[1], general->envp2);
		i++;
	}
}
