/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:35:26 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/09 16:39:14 by lmorelli         ###   ########.fr       */
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
int		handle_quotes(char *word);
int		compare_substrings(const char *str, const char *sub, size_t len);
void	lex_add_last(t_lex *head, t_lex *new);
void	expander(t_general *general);
void	show_quotes_error(char *word);
void	show_pathfinder_error(char *command);
void	manage_memory_error(void);
char	*find_substring_position(const char *str, const char *sub);
char	*find_substitution(char *command, t_general *general);
char	*calculate_first_part(char **first_part,
			char *input, char *position);
char	*calculate_final_part(char **second_part, char *end_command);
char	*find_end_command(char *position);
char	*replace_dollar_command(char *input, t_general *general);
t_lex	*new_lex_node(void);

#endif
