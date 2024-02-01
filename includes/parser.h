/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:35:26 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 16:11:11 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		iswhite(char c);
int		lexer(t_general *general);
int		parser(t_general *general);
int		what_token(char *str, int i);
int		pipe_status(t_general *general);
int		list_commander(t_general *general);
int		menage_token(char *str, int i, t_general *general, int *p);
int		quotes(char *str, int j);
void	lex_add_last(t_lex *head, t_lex *new);
t_lex	*new_lex_node(void);
void	expander(t_general *general);
void	show_quotes_error(char *word);
int		handle_quotes(char *word);
void	show_pathfinder_error(char *command);
void	manage_memory_error(void);

#endif
