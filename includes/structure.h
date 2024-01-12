/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:16:18 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/12 17:14:51 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_lex
{
	char			*command;
	char			**command2;
	int				token;
	//1 = |, 2 = >, 3 = <, 4 = >>, 5 = <<, 0 = é un comando
	int				pipe_status;
	//0 = prima pipe, 1 pipe in mezzo, 2 pipe finale
	int				builtin;
	struct s_lex	*next;
}	t_lex;

typedef struct s_general
{
	char			*args;
	char			**envp2;
	char			**enexp;
	char			**path;
	struct s_lex	*lexer;
}	t_general;

#endif
