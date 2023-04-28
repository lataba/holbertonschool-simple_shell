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
	int child_status, execve_status, output_status = 0;
	char **env = environ;

	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
	{
		if (fullpath != 0)
		{
			execve_status = execve(fullpath, array_tok, env);
			if (execve_status == -1)
				exit(errno);
		}
	}
	else
		wait(&child_status);

	if (WIFEXITED(child_status))
		output_status = WEXITSTATUS(child_status);

	return (output_status);
}

/**
 * free_arr - Frees an array of char pointers
 * @array: The array to be free
 */
void free_arr(char **array)
{
	int i;

	i = 0;
	for (i = 0; array[i] ; i++)
		free(array[i]);
	free(array);
}
