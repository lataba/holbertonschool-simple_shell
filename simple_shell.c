#include "shell.h"

/**
 * main - Simple shell
 * @argc: Number of arguments (unused)
 * @argv: Arguments passed to the program (unused)
 * Return: Exit value
 */

int main(void)
{
	char *line, **command;
	int built_status, path_status;
	size_t len;
	ssize_t nread;

	while (1)
	{
		len = 0;
		if (isatty(STDIN_FILENO) != 0)
			printf("$ ");
		nread = getline(&line, &len, stdin);

		if (nread == 1)
			exit(EXIT_SUCCESS);

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		command = store_tokens(line);

		built_status = builtin_execute(command);

		if (built_status == 0 || built_status == -1)
		{
			free(command);
			free(line);
		}
		if (built_status == 0)
			continue;
		if (built_status == -1)
			_exit(EXIT_SUCCESS);

		path_status = path_match(command);
		if (path_status == 0)
			fork_child(command[0], command);
		free(line);
	}
	return (0);
}
