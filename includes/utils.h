/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:44:08 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 17:39:24 by frdal-sa         ###   ########.fr       */
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
int		dumb_builtin_check(char *command);
int		matrixlen(char **matrix);
char	**matrix_dup(char **matrix);
char	**matrix_newline(char **matrix, char *str);
char	**maxxisplit(char const *s, char c);
int		matrixlen(char **matrix);
char	**matrix_dup(char **matrix);
void	print_matrix(char **matrix);
int		dumb_builtin_check(char *command);
char	*cleaner(char *str);
void	file_name_handler(t_lex *node);
char	*cleaner(char *str);
void	file_name_handler(t_lex *node);
char	**matrix_dup(char **matrix);

#endif
