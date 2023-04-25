#include "shell.h"

/**
 * main - Simple shell
 * @argc: Number of arguments (unused)
 * @argv: Arguments passed to the program (unused)
 * Return: Exit value
 */

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	char *line = NULL, **command; /*"line" guarda el comando del usuario, "command" guarda el comando en tokens*/
	size_t len = 0; /*tipo no signado, largo de line*/
	ssize_t nread; /*tipo signado, cantidad de tokens en que se divide line*/

	while (1)
	{
		len = 0;
		if (isatty(STDIN_FILENO) == 1) /*verifica si el programa se ejecuta en modo interactivo*/
			printf("$ "); /*si es en modo interactivo, imprime el prompt*/
		if (feof(stdin) == 1)
			break; /*si el usuario ingresa ctrl + D, EOF, corta la ejecucion*/

		nread = getline(&line, &len, stdin); /*se lee la linea ingresada por el usuario*/
		if (nread == -1) /*si getline falla, sale*/
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (nread > 0 && line[nread - 1] == '\n') /*si el usuario ingresa salto de linea, se cambia por fin de linea*/
			line[nread - 1] = '\0';
		command = store_tokens(line); /*command toma los valores de los tokens del line*/
		if (path_match(command) == 0) /*path_match busca el ejecutable del comando en el path*/
			fork_child(command[0], command); /*si se encuentra el ejecutable, se ejecuta crando un proceso hijo con fork_child*/
		free(line); /*se libera la linea*/
	}
	return (0);
}
