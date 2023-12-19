/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:44:08 by jcardina          #+#    #+#             */
/*   Updated: 2023/12/19 16:49:19 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_matrix(char **matrix);
void	print_export(char **matrix);
void	print_matrix(char **matrix);
int		dumb_builtin_check(char *command);
int		matrixlen(char **matrix);
char	**matrix_dup(char **matrix);
char	**matrix_newline(char **matrix, char *str);

#endif
