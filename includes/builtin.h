#ifndef BUILTIN_H
#define BUILTIN_H

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

#endif
