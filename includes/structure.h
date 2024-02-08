/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:16:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/08 22:49:11 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_lex
{
	char			*command;
	char			**command2;
	int				token;
	// 0= comando, 1 = |, 2 = >, 3 = >>, 4 = <, 5 = << COMMENTO DA NON ELIMINARE
	int				pipe_status;
	int				builtin;
	int				i;
	struct s_lex	*next;
}	t_lex;

typedef struct s_general
{
	char			*args;
	char			**envp2;
	char			**enexp;
	char			**path;
	struct s_lex	*lexer;
	int				file_fd;
	int				input_fd;
	int				hd_fd;
	int				o_flag;
	int				save_exit_status;
	int				flag_quotes[1000];
	int				spiping;
}	t_general;

#endif
