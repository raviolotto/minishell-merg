/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:16:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/15 16:21:44 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_lex
{
	char			*main_command;
	char			**arguments;
	int				token;
	// 0= comando, 1 = |, 2 = >, 3 = >>, 4 = <, 5 = << COMMENTO DA NON ELIMINARE
	int				pipe_status;
	int				builtin;
	int				i;
	struct s_lex	*next;
}	t_lex;

typedef struct s_general
{
	char			*user_input;
	char			**environment_variables;
	char			**expanded_environment;
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
