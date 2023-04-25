#include "shell.h"

/**
 * store_tokens - Funcion that separates the line in arguments
 * @line: The line that user writes on the stdin
 * Return: A double poniter to an array that stores the arguments (tokens)
 */

char **store_tokens(char *line)
{
	char **array_tok = NULL, *token = NULL; /*variables que guardan los tokens*/
	int i = 0, line_len = 0;

	if (line == NULL) /*si la linea no es valida devuelve puntero nulo*/
		return (NULL);

	line_len = str_count(line); /*line_len guarda la cantidad de palabras que vienen en la linea*/

	array_tok = malloc(sizeof(char *) * (line_len + 1)); /*se asigna la memoria para el array*/
	if (array_tok == NULL) /*si malloc falla, sale*/
		return (NULL);

	token = strtok(line, "\n\t "); /*se separa la linea en tokens*/
	while (token != NULL)
	{
		array_tok[i] = strdup(token); /*se guardan los tokens en el array*/
		if (array_tok[i] == NULL) /*si falla el duplicado de un token*/
		{
			free_arr(array_tok); /*se libera toda la memoria utilizada antes y sale*/
			return (NULL);
		}
		token = strtok(NULL, "\t\n ");
		i++;
	}
	array_tok[i] = NULL; /*se apunta el ultimo elemento a null*/
	return (array_tok); /*la funcion devuelve el array de tokens*/
}

/**
 * str_count - Function that ounts the number of words in a string
 * @str: The line given by the user
 * Return: The number of words in the string line
 */
int str_count(char *str)
{
	int i, flag = 1, count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ' ' && flag == 1)
		{
			count += 1;
			flag = 0; /*flag es cero si el caracter no es un espacio*/
		}
		if (str[i + 1] == ' ')
			flag = 1; /*flag es 1 si se encuentra un espacio*/
	}
	return (count);
}

/**
 * free_arr - Frees an array of char pointers
 * @array: The array to be free
 */
void free_arr(char **array)
{
	int i;

	i = 0;
	for (i = 0; array[i] ; i++) /*se libera cada celda del array*/
		free(array[i]);
	free(array); /*se libera el array*/
}

/**
 * get_env - Function that gets the value of enviroment variable.
 * @var_name: The name of the enviroment variable.
 * Return: The value of the environment Variable or NULL.
 */

char *get_env(char *var_name)
{
	int i = 0;
	char *var_value; /*el valor que viene en el PATH*/
	size_t len_value, len_name = strlen(var_name);

	while (environ[i] != NULL) /*recorido por las variables de entorno*/

	{
		len_value = strlen(environ[i]); /*largo de la variable*/
		var_value = malloc((len_value + 1) * sizeof(char)); /*asignacion de memoria para la variable*/
		if (var_value == NULL) /*revision de malloc, si falla termina*/
		{
			perror("malloc");
			return (NULL);
		}
		if (strncmp(var_name, environ[i], len_name) == 0)
		/*se compara el nombre de la variable buscada con la encontrada en environ*/
		/*si coincide se copia el contenido de environ[i] y la funcion devuelve su valor*/
		{
			strcpy(var_value, environ[i]);
			return (var_value);
		}
		free(var_value); /*si no coincide se libera la memoria y sigue buscando*/
		i++;
	}
	free(var_value);
	return (NULL);
}

/**
 * path_match -  Searchs for the command in the path
 * @array_tok: The array of tokens containing the user line command
 * Return: 0 if success, 1 if fail
 */
int path_match(char **array_tok)
{
	char *path, *fullpath, *path_value;
	struct stat ex;

	path = get_env("PATH"); /*se guarda en path el valor de la variable de entorno obtenido con get_env*/
	path_value = strtok(path, ":"); /*se divide en tokens el contenido del PATH*/
	while (path_value != NULL)
	{
		fullpath = fullpath_func(*array_tok, path_value); /*se contruye la ruta completa de busqueda del comando*/
		if (stat(fullpath, &ex) == 0) /*si en esa ruta se encuentra el archivo ejecutable*/
		{
			*array_tok = strdup(fullpath); /*se guarda la ruta completa en array_tok*/
			free(fullpath);
			free(path);
			return (0);
		}
		free(fullpath);
		path_value = strtok(NULL, ":");
	}
	free(path);

	return (1);
}

/**
 * fullpath_func - Function that concatenates the fullpath
 * @array_tok: The tokens
 * @path_value: The path value
 * Return: A pointer to the complete command
 */

char *fullpath_func(char *array_tok, char *path_value)
{
	char *command; /*ruta completa de busqueda del comando*/
	size_t len = 0;

	len = strlen(path_value) + strlen(array_tok) + 2; /*largo de la cadena +2 para / y el nulo de strcat*/
	command = malloc(sizeof(char) * len);
	if (command == NULL) /*se verifica la reserva de memoria, si falla sale*/
	{
		return (NULL);
	}

	memset(command, 0, len); /*inicializacion del array que guardara el comando*/

	command = strcat(command, path_value);
	command = strcat(command, "/");
	command = strcat(command, array_tok); /*concatenacion del valor del path con el comando del usuario*/

	return (command);
}
