/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:35:26 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/08 14:50:50 by lmorelli         ###   ########.fr       */
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
void	free_lex(t_lex *head);
void	afalcons(t_lex *node);
void	lex_add_last(t_lex *head, t_lex *new);
t_lex	*new_lex_node(void);

int execute_external_command(char **args);

#endif
