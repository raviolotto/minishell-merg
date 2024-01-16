/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:18:23 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/16 18:44:01 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	handle_exit(char **args);
void	handle_cd(t_general *general, t_lex *node);
void	handle_pwd(void);
void	handle_export(t_general *general, t_lex *node);
void	handle_unset(t_general *general, t_lex *node);
void	handle_env(t_general *general);
void	handle_echo(t_general *general, t_lex *node);
int		my_setenv(char *name, char *value, char ***environ);

void	ft_supp_rm(char *str, char c);
int		ft_idx_quotes(char *str, char c);
int		ft_nb_quotes(char *str, char c);
int		ft_rm_quotes(char *str, int s_quote, int d_quotes, int idx_double);
int		ft_cd_with_quotes(char *str);
int		ft_cd_only(char **env, char **command2,
			t_general *general, char *old_dir);
int		ft_change_dir(char *new_dir, char **cmd2,
			t_general *general, char *old_dir);

#endif
