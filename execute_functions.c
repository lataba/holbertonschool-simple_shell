#include "shell.h"

/**
 * fork_child - Function that creats a child process
 * @array_tok: the tokenidez command line given by the user
 * Return: 0 if success, -1 if fail
 */

int fork_child(char **array_tok)
{
	pid_t pid;
	int child_status, output_status = 0;
	char **env = environ;

	pid = fork(); /*fork call to creat a new process*/
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (pid == 0) /*execute the command inside a child process*/
	{
		if (strncmp(*array_tok, "/", 1) != 0 && strncmp(*array_tok, "./", 2) != 0)
			if (path_match(array_tok) == 127)
			{
				dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", array_tok[0]);
				return (127);
			}
		if (execve(*array_tok, array_tok, env) == -1)
		{
			dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", array_tok[0]);
			return (127);
		}
	}
	wait(&child_status); /*parent process waiting for the child process finish*/

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
		free(array[i]); /*free each*/
	free(array); /*free all*/
}
