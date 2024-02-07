/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/07 17:47:23 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

// #define BUFFER_SIZE 1024

// int re_here_doc(t_lex *node, t_general *general, int *save_fd)
// {
//     char *delimiter; // Considera il delimitatore dopo "<<"
// 	int i;

// 	i = 0;
// 	while (general->args[i] != '<') //questa roba va bene in tutti i casi?
// 		i++;
// 	i += 2;
// 	while (general->args[i] == ' ')
// 		i++;
// 	delimiter = general->args + i;
//     ft_printf("Delimitatore: %s\n", delimiter);

// 	char buffer[BUFFER_SIZE];
// 	while (1)
// 	{
//     	size_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));

//     	if (bytesRead == -1)
//     	{
//         	perror("Errore nella lettura da stdin");
//         	exit(EXIT_FAILURE);
//     	}
//     	else if (bytesRead == 0)
//         	break;
//     	char *delimiterPos = strstr(buffer, delimiter);
//     	if (delimiterPos != NULL)
//     	{
// 			if (node->builtin > 0)
// 			{
//         		builtinmanager(node, general);
//         		dup2(save_fd[0], STDIN_FILENO);
//         		exit(g_last_exit_status);
//     		}
// 			write(1, "delimitatore trovato\n", 21);
//         	break;
//     	}
// 	}
// 	close(STDIN_FILENO);

// 	ft_printf("\nCOMANDO : %s\nMATRICE : ", node->command2[0]);
// 	print_matrix(node->command2);
//  	execve(node->command2[0], node->command2, NULL);
// }

char	*create_new_doc_name(void)
{
	char			*doc_name;
	char			*doc_nb;
	char			*full_name;
	int				doc_idx;

	doc_idx = 0;
	doc_name = "here_docs-";
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

int	re_here_doc(t_lex *node, t_general *general, int *save_fd)
{
	char	*delimiter;
	char	*here_doc;
	char	*str;
	char	*expander_result;
	int		i;
	int		pid;
	int		file;

	i = 0;
	while (general->args[i] != '<') //questa roba va bene in tutti i casi?
		i++;
	i += 2;
	while (general->args[i] == ' ')
		i++;
	if (handle_quotes(general->args + i) == 1)
		exit(1); //che exit status ha "you didn't close the '""
	ft_cd_with_quotes(general->args + i, general, i);
	delimiter = general->args + i;
	ft_printf("Delimitatore: %s\n", delimiter);
	here_doc = create_new_doc_name();
	printf("doc name: %s \n", here_doc);
	file = open(here_doc, O_WRONLY | O_TRUNC | O_CREAT, 0644); //generare nome in maniera dinamica
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
	close(file);
//capire se é possibile richiamarsi la funzione gia
//esistente senza riscrivere tutto cio che sta qui sotto
	general->file_fd = open(here_doc, O_RDONLY);
	if (general->file_fd == -1)
	{
		perror("Errore nell'apertura del file");
		g_last_exit_status = 1; // 1 va bene?
		exit(g_last_exit_status);
	}
	dup2(general->file_fd, STDIN_FILENO);
	close(general->file_fd);
	if (node->builtin > 0)
	{
		builtinmanager(node, general);
		dup2(save_fd[0], STDIN_FILENO);
		exit(g_last_exit_status);
	}
	execve(node->command2[0], node->command2, NULL);
}

int	re_out(t_lex *node, t_general *general, int *save_fd)
{
	dup2(general->file_fd, STDOUT_FILENO);
	close(general->file_fd);
	if (node->builtin > 0)
	{
		builtinmanager(node, general);
		dup2(save_fd[1], STDOUT_FILENO);
		exit (g_last_exit_status);
	}
	execve(node->command2[0], node->command2, NULL);
}

int	piping(int *fd, int *save_fd, t_lex *node, t_general *general)
{
	if (node->next && node->next->token == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	else if (node->next == NULL)
		dup2(save_fd[1], STDOUT_FILENO);
	if (node->builtin == 1 || node->builtin == 3 || node->builtin == 6)
	{
		builtinmanager(node, general);
		exit (g_last_exit_status);
	}
	execve(node->command2[0], node->command2, NULL);
	perror("il comando esterno non é stato eseguito\n");
}

int	execute_command(t_lex *node, t_general *general, int *save_fd)
{
	int	pid;
	int	fd[2];
	int	status;

	if (node->builtin != 1 && node->builtin != 3
		&& node->builtin != 6 && node->builtin != 0)
	{
		builtinmanager(node, general);
		return (g_last_exit_status);
	}
	if (node->next && node->next->token == 1)
	{
		if (pipe(fd) == -1)
			perror("non é stato possibile creare la pipe");
	}
	pid = fork();
	if (pid == 0)
	{
		if (general->o_flag == 1)
		{
			re_out(node, general, save_fd);
			close(fd[0]);
			close(fd[1]);
		}
		else if (node->next == NULL || node->next->token == 1)
			piping(fd, save_fd, node, general);
		else if (node->next->token == 2 || node->next->token == 3)
			re_out(node, general, save_fd);
		else if (node->next->token == 4)
			re_in(node, general, save_fd);
 		else if (node->next->token == 5)
			re_here_doc(node, general, save_fd);
	}
	waitpid(pid, &status, 0);
	wait(NULL);
	if (node->next && node->next->token == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

void	executor(t_general *general)
{
	t_lex	*tmp;
	int		save_fd[2];
	int		flag;

	if (g_last_exit_status != 0 && g_last_exit_status != 130)
		return ;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	general->o_flag = re_dir_status(open_fd(general,
				find_correct_redir(general)), general);
	tmp = general->lexer;
	while (tmp)
	{
		if (tmp->token == 0)
			g_last_exit_status = execute_command(tmp, general, save_fd);
		tmp = tmp->next;
	}
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
	general->save_exit_status = g_last_exit_status;
}
