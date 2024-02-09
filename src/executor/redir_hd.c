/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:34:56 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/09 16:15:23 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	find_redir_hd(t_general *general)
{
	t_lex	*node;
	int		i;

	i = -1;
	node = general->lexer;
	while (node)
	{
		if (node->token == 5)
			i = node->i;
		node = node->next;
	}
	return (i);
}

void	hd_son_routine(t_lex *node, t_general *general, int file)
{
	char	*str;
	char	*expander_result;

	while (1)
	{
		str = readline("heredoc> ");
		if (!str)
		{
			free(str);
			g_last_exit_status = 1;
			ft_printf("> kitty shell: warning: here-document \
delimited by end-of-file\n");
			exit(g_last_exit_status);
		}
		if (ft_strncmp(str, node->command, ft_strlen(node->command)) == 0)
		{
			free(str);
			break ;
		}
		expander_result = replace_dollar_command(str, general);
		write(file, expander_result, ft_strlen(expander_result));
		write(file, &"\n", 1);
		free(str);
	}
}

int	re_here_doc(t_lex *node, t_general *general, int index)
{
	char	*here_doc;
	int		pid;
	int		file;

	here_doc = ".here_docs";
	file = open(here_doc, O_RDWR | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	if (pid == 0)
	{
		hd_son_routine(node, general, file);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (index == node->i)
		general->hd_fd = open(here_doc, O_RDONLY);
	unlink(here_doc);
	close(file);
}

int	hd_manager(t_general *general)
{
	int		index;
	t_lex	*node;

	index = find_redir_hd(general);
	node = general->lexer;
	while (node)
	{
		if (node->token == 5)
			re_here_doc(node, general, index);
		node = node->next;
	}
	return (index);
}
