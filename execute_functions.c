#include "shell.h"

/**
 * fork_child - Function that creats a child process
 * @fullpath: full path of the executable file of the command
 * @array_tok: the tokenidez command line given by the user 
 * Return: 0 if success, -1 if fail
 */

int fork_child(char *fullpath, char **array_tok)
{
	pid_t pid;
	int child_status, execve_status;
	char **env = environ;

	pid = fork(); /*llamado a fork para crear proceso hijo*/
	if (pid == -1) /*error al crear el proceso hijo*/
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) /*si fork devuelve 0, el proceso hijo ejecuta el programa con la llamada a execve()*/
	{
		execve_status = execve(fullpath, array_tok, env); /*ejecucion con la ruta completa, argumentos y variables de entorno*/
		if (execve_status == -1)
			return (-1); /*falla en la ejecucion dentro del proceso hijo*/
	}
	else
		wait(&child_status); /*el proceso padre espera la finalizacion del hijo, si es exitosa devuelve el PID del hijo*/

	return (0);
}
