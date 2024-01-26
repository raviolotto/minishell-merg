/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:44:08 by jcardina          #+#    #+#             */
/*   Updated: 2024/01/26 16:12:27 by jcardina         ###   ########.fr       */
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

#endif
