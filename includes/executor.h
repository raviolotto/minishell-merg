/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:23:13 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/02 17:58:14 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		find_correct_redir(t_general *general);
void	executor(t_general *general);
void	builtinmanager(t_lex *node, t_general *general);
void	builtinmanager(t_lex *node, t_general *general);
void	open_fd(t_general *general, int i);

#endif
