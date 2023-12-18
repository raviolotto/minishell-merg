#ifndef BUILTIN_H
#define BUILTIN_H

void	handle_pwd(void);
void	handle_export(t_general *general, t_lex *node);
//void	handle_unset(t_general *general, t_lex *node);
void	handle_unset(t_general *general, t_lex *node);
void	handle_env(t_general *general);
int		my_setenv(char *name, char *value, char ***environ);

#endif
