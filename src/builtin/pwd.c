#include "../../includes/mini_shell.h"

void	handle_pwd(void)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		ft_printf("%s\n", current_directory);
	else 
		perror("pwd");
}