#include "shell.h"

/**
 * main - Simple shell
 * @argc: numbert of arguments (unused)
 * @argv: arguments passed to the program (unused)
 * Return: Exit value
 */

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
/*	int status = 0;*/
	char *line = NULL, **command; /***fullpath;*/
	size_t len = 0; /*tipo no signado, tamanio de un objeto en bytes*/
	ssize_t nread; /*tipo signado, tamanio o indice que puede ser negativo*/

	while (1)
	{
		len = 0;
		if (isatty(STDIN_FILENO))
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (line[0] == '\0')
			continue;
		if (feof(stdin) == 1)
		{
			free(line);
			break;
		}
		if (nread == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		command = store_tokens(line);
		if (path_match(command) == 0)
			fork_child(command[0], command);
		free(line);
	}
	return (0);
}
