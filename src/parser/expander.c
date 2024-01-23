/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:29 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/23 19:00:57 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int confronta_sottostringhe(const char* str, const char* sub, size_t len) {
    size_t i = 0;
    while (i < len) {
        if (str[i] != sub[i]) {
            return 0; 
        }
        i++;
    }
    return 1;  
}

char *find_substring_position(const char* str, const char* sub) {
    size_t len = ft_strlen(sub);
    while (*str != '\0') {
        if (confronta_sottostringhe(str, sub, len)) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

char *find_sostituzione(char *comando, t_general *general) {
    int index = my_setenv(comando + 1, NULL, &general->envp2);
    if (index >= 0) {
        char *sostituzione = ft_strchr(general->envp2[index], '=') + 1;
        return sostituzione;
    } else {
        return "";
    }
}

char *sostituisci_comando_dollaro(char *input, t_general *general) {
    char *posizione = input;
	char *sostituzione;

    // Trova la posizione del primo comando
    while ((posizione = find_substring_position(posizione, "$")) != NULL) {
        char *fine_comando = posizione + ft_strlen("$");

        // Trova la fine del comando
        while (*fine_comando != ' ' && *fine_comando != '\0' && *fine_comando != '\"' && *fine_comando != '$' && *fine_comando != '\'') {
            fine_comando++;
        }
        // Calcola la lunghezza del comando
        int lunghezza_comando = fine_comando - posizione;
        char *comando = ft_substr(posizione, 0, lunghezza_comando);
		printf("comando! %s\n", comando);
		
		if (strncmp(comando, "$?", 2) == 0)
			sostituzione = ft_itoa(g_last_exit_status);
        else 
			sostituzione = find_sostituzione(comando, general);

        char *parte_prima = ft_substr(input, 0, posizione - input);
        char *parte_dopo = ft_substr(fine_comando, 0, strlen(fine_comando));

        char *updated_input = ft_strjoin(parte_prima, sostituzione);
        updated_input = ft_strjoin(updated_input, parte_dopo);

        free(input);
        free(parte_prima);
        free(parte_dopo);
        free(comando);

        return sostituisci_comando_dollaro(updated_input, general);
    }
    return input;
}

void	ft_expander_case(char **line, int flag, t_general *general, char *dollar)
{
	char *finale = sostituisci_comando_dollaro(*line, general);
	//printf("finale! %s\n", finale);
	*line = finale;
	//free(finale);
}

char	*ft_str_dollar_cpy(char *src)
{
	int		a;
	char	*dest;

	dest = malloc(sizeof (char *) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	a = 0;
	while (src[a])
	{
		if (src[a] == '$')
			return (dest);
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}


void	node_expander(char **command2, t_general *general)
{
	int		i;
	int		j;
	int		idx;
	int		flag;
	char	*dollar;

	i = -1;
	flag = 0;
	while(command2[++i])
	{
		//printf("%i\n", general->flag_quotes[i]);
		if (general->flag_quotes[i] != 1)
		{
			j = 0;
			while (command2[i][j] != '\0')
			{
				idx = ft_idx_quotes(command2[i], '$');
				if (ft_strchr(command2[i], '$') && idx != 0)
				{
					dollar = ft_str_dollar_cpy(command2[i]);
					flag = 1;
				}
				j++;
			}
		//if(expander_status(&command2[i], dollar) == 0)
			ft_expander_case(&command2[i], flag, general, dollar);
		}
	}
	//free(dollar);
}

void	expander(t_general *general)
{
	t_lex	*tmp;

	tmp = general->lexer;
	while(tmp)
	{
		node_expander(tmp->command2, general);
		tmp = tmp->next;
	}
}
