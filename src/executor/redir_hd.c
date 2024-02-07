/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:34:56 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/07 22:48:59 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	find_redir_hd(t_general *general)
{
	t_lex *node;
	int i;

	i = -1;
	node = general->lexer;
	while(node)
	{
		if(node->token == 5)
			i = node->i;
		node = node->next;
	}
	return (i);
}

char	*create_new_doc_name(void)
{
	char			*doc_name;
	char			*doc_nb;
	char			*full_name;
	int				doc_idx;

	doc_idx = 0;
	doc_name = ".here_docs-";
	while (1)
	{
		doc_nb = ft_itoa(doc_idx);
		full_name = ft_strjoin(doc_name, doc_nb);
		if (access(full_name, R_OK | W_OK) != 0)
		{
			free(doc_nb);
			break ;
		}
		free(doc_nb);
		free(full_name);
		doc_idx++;
	}
	return (full_name);
}
//probabilmente devi freeare docname

//return index;
//da aggiungere int index
int	re_here_doc(t_lex *node, t_general *general, int index)
{
	char	*delimiter;
	char	*here_doc;
	char	*str;
	char	*expander_result;
	//int		i;
	int		pid;
	int		file;

	// i = 0;
	// while (general->args[i] != '<') //questa roba va bene in tutti i casi?
	// 	i++;
	// i += 2;
	// while (general->args[i] == ' ')
	// 	i++;
	// if (handle_quotes(general->args + i) == 1)
	// 	exit(1); //che exit status ha "you didn't close the '""
	// ft_cd_with_quotes(general->args + i, general, i);
	delimiter = node->command;
	ft_printf("Delimitatore: %s\n", delimiter);
	here_doc = create_new_doc_name();
	printf("doc name: %s \n", here_doc);
	file = open(here_doc, O_RDWR | O_TRUNC | O_CREAT, 0777); //generare nome in maniera dinamica
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			str = readline("heredoc> ");
			if (!str)
			{
				free(str);
				g_last_exit_status = 1; // 1 va bene?
				exit(g_last_exit_status);
			}
			if (ft_strncmp(str, delimiter, ft_strlen(delimiter)) == 0)
				break ;
			expander_result = sostituisci_comando_dollaro(str, general);
			write(file, expander_result, ft_strlen(expander_result));
			write(file, &"\n", 1);
			free(str);
			//free di expander result?
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if(index == node->i)
	{
		// ft_printf("questo é open %d\n", open(here_doc, O_RDONLY));
		// ft_printf("questo é open %d\n", open(here_doc, O_RDONLY));
		// ft_printf("questo é file %d\n", file);
		general->hd_fd = open(here_doc, O_RDONLY);
	}
	else
		unlink(here_doc);
	close(file);
//capire se é possibile richiamarsi la funzione gia
//esistente senza riscrivere tutto cio che sta qui sotto
	// general->file_fd = open(here_doc, O_RDONLY);
	// if (general->file_fd == -1)
	// {
	// 	perror("Errore nell'apertura del file");
	// 	g_last_exit_status = 1; // 1 va bene?
	// 	exit(g_last_exit_status);
	// }
	// dup2(general->file_fd, STDIN_FILENO);
	// close(general->file_fd);
	// if (node->builtin > 0)
	// {
	// 	builtinmanager(node, general);
	// 	dup2(save_fd[0], STDIN_FILENO);
	// 	exit(g_last_exit_status);
	// }
	// execve(node->command2[0], node->command2, NULL);
}

int	hd_manager(t_general *general)
{
	int		index;
	t_lex	*node;

	index = find_redir_hd(general);
	node = general->lexer;
	while(node)
	{
		if(node->token == 5)
		{
			re_here_doc(node, general, index); //da cambire per ricevere un solo nodo e index
		}
		node = node->next;
	}
	return (index);
}