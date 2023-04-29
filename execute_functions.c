#include "shell.h"

/**
 * fork_child - Function that creats a child process
 * @fullpath: full path of the executable file of the command
 * @array_tok: the tokenidez command line given by the user
 * Return: 0 if success, -1 if fail
 */

int fork_child(char **array_tok)
{
	pid_t pid;
	int child_status, output_status = 0;
	char **env = environ;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (pid == 0)
	{
		if (strncmp(*array_tok, "/", 1) != 0 && strncmp(*array_tok, "./", 2) != 0)
			path_match(array_tok);
		if (execve(*array_tok, array_tok, env) == -1)
		{
			perror("Shell");
			exit(errno);
		}
	}
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
