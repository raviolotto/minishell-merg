/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:23:13 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/07 22:00:33 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		find_correct_redir(t_general *general);
int		open_fd(t_general *general, int i);
int		re_dir_status(int index, t_general *general);
int		re_in(t_lex *node, t_general *general, int *save_fd);
int		fd_redirin1(t_general *general);
int		re_out(t_lex *node, t_general *general, int *save_fd);
int		hd_manager(t_general *general);
void	executor(t_general *general);
void	builtinmanager(t_lex *node, t_general *general);

#endif
