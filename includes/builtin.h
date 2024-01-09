#ifndef BUILTIN_H
#define BUILTIN_H

void	handle_cd(t_general *general, t_lex *node);
void	handle_pwd(void);
void	handle_export(t_general *general, t_lex *node);
void	handle_unset(t_general *general, t_lex *node);
void	handle_env(t_general *general);
int		my_setenv(char *name, char *value, char ***environ);

void	ft_remove_char_in_str(char *str, char c);
int		ft_find_char_index_str(char *str, char c);
int		ft_count_char(char *str, char c);
int		ft_remove_quotes(char *str, int single_quote, int double_quotes,
	int index_double_quotes);
int		ft_cd_with_quotes(char *str);

#endif
