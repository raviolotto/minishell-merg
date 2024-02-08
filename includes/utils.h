/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:44:08 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/08 19:32:37 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_matrix(char **matrix);
void	free_lex(t_lex *head);
void	afalcons(t_lex *node);
void	free_general(t_general *general);
void	free_and_exit(int exit_n, t_general *general);
void	print_export(char **matrix);
void	print_matrix(char **matrix);
void	index_list(t_general *general);
void	file_name_handler(t_lex *node);
void	print_matrix(char **matrix);
void	file_name_handler(t_lex *node);
int		dumb_builtin_check(char *command);
int		matrixlen(char **matrix);
int		matrixlen(char **matrix);
int		dumb_builtin_check(char *command);
char	**matrix_dup(char **matrix);
char	**matrix_newline(char **matrix, char *str);
char	**maxxisplit(char const *s, char c);
char	**matrix_dup(char **matrix);
char	*cleaner(char *str);
char	*cleaner(char *str);
char	**matrix_dup(char **matrix);
char	*ft_strjoin2(char *s1, char *s2);
int		is_whitespace_input(const char *str);

#endif
