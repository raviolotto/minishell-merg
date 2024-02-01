/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:16:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 18:00:06 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_lex
{
	char			*command;
	char			**command2;
	int				token; // 0 comando, 1 pipe, 2 > , 3 >> ,4 < ,5 <<
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
	int				flag_quotes[1000];
}	t_general;

#endif
