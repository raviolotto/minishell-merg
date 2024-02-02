/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:49:11 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/02 18:16:18 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/mini_shell.h"

// int	re_out(t_lex *node, t_general *general, int *save_fd)
// {
// 	int	file;

// 	if(node->next->token == 2)
// 		file = open(node->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if(node->next->token == 3)
// 		file = open(node->next->command, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (file == -1)
// 		return (1);
// 	dup2(file, STDOUT_FILENO);
// 	close(file);
// 	if (node->builtin > 0)
// 	{
// 		builtinmanager(node, general);
// 		dup2(save_fd[1], STDOUT_FILENO);
// 		exit (g_last_exit_status); //potrebbe essere utile returnare exit status?
// 	}
// 	execve(node->command2[0], node->command2, NULL);
// }

int	re_out(t_lex *node, t_general *general, int *save_fd)
{
	dup2(general->file_fd, STDOUT_FILENO);
	close(general->file_fd);
	if (node->builtin > 0)
	{
		builtinmanager(node, general);
		dup2(save_fd[1], STDOUT_FILENO);
		exit (g_last_exit_status); //potrebbe essere utile returnare exit status?
	}
	execve(node->command2[0], node->command2, NULL);
}

int	piping(int *fd, int *save_fd, t_lex *node, t_general *general)
{
	if(node->next && node->next->token == 1)
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
		exit (g_last_exit_status); //potrebbe essere utile returnare exit status?
	}
	execve(node->command2[0], node->command2, NULL);
	perror("il comando esterno non é stato eseguito\n");
}

int	execute_command(t_lex *node, t_general *general, int *save_fd)
{
	int	pid;
	int	fd[2];
	int	status;


	if(node->builtin != 1 && node->builtin != 3 && node->builtin != 6 && node->builtin != 0)
	{
		builtinmanager(node, general);
		return(g_last_exit_status);
	}
	if(node->next && node->next->token == 1)
	{
		if (pipe(fd) == -1)
			perror("non é stato possibile creare la pipe");
	}
	pid = fork();
	if (pid == 0)
	{
			if(node->next == NULL || node->next->token == 1)
				piping(fd, save_fd, node, general);
			else if(node->next->token == 2 || node->next->token == 3)
				re_out(node, general, save_fd);
			else
				write(1, "p\n", 2);
	}
	waitpid(pid, &status, 0);
	wait(NULL);
	if (node->next && node->next->token == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	return WIFEXITED(status) && WEXITSTATUS(status);
}
void	executor(t_general *general)
{
	t_lex	*tmp;
	int		save_fd[2];
	int		i;

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	i = find_correct_redir(general);
	open_fd(general, i);
	tmp = general->lexer;
	while (tmp)
	{
		if(tmp->token == 0)
			g_last_exit_status = execute_command(tmp, general, save_fd);
		tmp = tmp->next;
	}
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}
