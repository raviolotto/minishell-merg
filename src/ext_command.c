/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:07:51 by lmorelli          #+#    #+#             */
/*   Updated: 2024/01/24 16:34:38 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	execute_external_command(char **args)
{
	pid_t	pid;
	int		status;
	char	**token;
	int		i;
	char	*res;

	token = ft_split(args[0], '/');
	i = 0;
	res = ft_strdup("/");
	while (token[i])
	{
		res = ft_strjoin(res, "/");
		res = ft_strjoin(res, token[i]);
		i++;
	}
	if (access(res, X_OK) == 0)
	{
		pid = fork();
		if (pid < 0)
			perror("fork error");
		else if (pid == 0)
		{//execve va chiamato nel child altrimenti il parent verrebbe sostituito e non riuscirebbe ad aspettare che il child termini
			printf("\nFIGLIO\n");//se aggiungessi qualcos altro dopo questa riga tipo un printf non stamperebbe nulla perché execve rimpiazza tutto ció che sta nel child
			execve(res, args, NULL);
			
		}
		else
		{printf("\nPADRE\n");
			wait(&status);
			if (WIFEXITED(status))
			{
				g_last_exit_status = WEXITSTATUS(status);
				if (g_last_exit_status == 0)
					printf("\nsuccess = %d\n", g_last_exit_status);
				else
					printf("\nfailure = %d\n", g_last_exit_status);
}
			// while (!WIFEXITED(status) && !WIFSIGNALED(status))
			// 	waitpid(pid, &status, 0);
		}
		free(res);
		return (1);
	}
// perror("error, the command doesn't exist or you don't have the necessary permissions");
	free(res);
	return (0);
}

/*

WIFEXITED e WIFSIGNALED sono macro definite nella libreria <sys/wait.h>
WIFEXITED(status): Restituisce un valore diverso da zero se il processo figlio è terminato normalmente.
WIFSIGNALED(status): Restituisce un valore diverso da zero se il processo figlio è stato terminato da un segnale.

Come funziona fork:

-Duplicazione del processo: Quando chiami fork, il sistema operativo crea una copia esatta del processo chiamato "processo figlio".
 Entrambi i processi (il processo padre e il processo figlio) iniziano a eseguire l'istruzione successiva a fork.

-Valore restituito dal fork: Nel processo padre, fork restituisce il PID (Process ID) del processo figlio appena creato. Nel processo figlio, fork restituisce 0.

-Separazione del PID: Il PID (Process ID) identifica univocamente ogni processo. Dopo una chiamata a fork, ci sono due processi distinti con PID diversi: il processo padre e il processo figlio.

-Duplicazione dei file descriptor: I file descriptor aperti nel processo padre vengono duplicati nel processo figlio.
 Ciò significa che il processo padre e il processo figlio condivideranno gli stessi file aperti. Questo include i file, i socket, le pipe e altri oggetti di sistema.

*/
