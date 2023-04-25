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

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve_status = execve(fullpath, array_tok, env);
		if (execve_status == -1)
			return (-1);
	}
	else
		wait(&child_status);

	return (0);
}
