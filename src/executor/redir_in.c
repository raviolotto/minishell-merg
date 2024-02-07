/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:02 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/07 18:21:18 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/*
NELLA NOSTRA SHELL :
kitty shell> cat < file1.txt | grep s
idx = 6
Errore nell'apertura del file: No such file or directory
...e rimane in attesa

IN BASH :
lmorelli@e4r9p4:~/Desktop/mini_3febbr$ cat < file1.txt | grep s
includes
minishell
src
*/
int	re_in(t_lex *node, t_general *general, int *save_fd)
{
	int	i;

	i = 0;
	while (general->args[i] != '<') //questa roba va bene in tutti i casi?
		i++;
	i++;
	while (general->args[i] == ' ')
		i++;
	ft_printf("args = %s\n", general->args + i);
	handle_quotes(general->args + i);
	ft_cd_with_quotes(general->args + i, general, i);
	ft_printf("idx = %d\n", i);
	ft_printf("args = %c\n", general->args[i + 1]);
	general->file_fd = open(general->args + i, O_RDONLY);
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
