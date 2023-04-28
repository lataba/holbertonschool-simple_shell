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

/**
 * shell_exit - Exits the shell
 * Return: void
 */

int shell_exit(void)
{
	return (-1);
}


/**
 * shell_env - prints environment
 * Return: void
 */

int shell_env(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

/**
 **builtin_execute - executes the built in functions
 **@tokens: arguments being passed
 **Return: tokens
 **/
int builtin_execute(char **tokens)
{
	int status;
	unsigned int length;
	unsigned int num;
	unsigned int i;

	built_s builtin[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{NULL, NULL}
	};

	if (tokens[0] == NULL)
		return (1);

	length = strlen(tokens[0]);

	num = shell_num_builtins(builtin);
	for (i = 0; i < num; i++)
	{
		if (strncmp(tokens[0], builtin[i].name, length) == 0)
		{
			status = (builtin[i].p)();
			return (status);
		}
	}
	return (1);
}

/**
 **shell_num_builtins - this check num built-ins
 **@builtin: takes the builtin to be counted
 **Return: num of built-ins
 **/

int shell_num_builtins(built_s builtin[])
{
	unsigned int i;

	i = 0;
	while (builtin[i].name != NULL)
		i++;

	return (i);
}
