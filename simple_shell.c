#include "main.h"

int main(void)
{
	char *line = NULL; /* inicializa un puntero a char para almacenar la línea ingresada por el usuario */
	size_t bufsize = 0; /* tamaño inicial del buffer que getline asignará de forma dinámica */
	char **argv = NULL; /* inicializa un puntero a puntero a char para almacenar los argumentos ingresados por el usuario */
	int i = 0, size = 0;

	signal(SIGINT, ig_ctrlc); /* detecta que si es ctrl + C imprime '\n' y si es ctrl + D termina */

	while(1)
	{
		printf("$ ");

		if (getline(&line, &bufsize, stdin) == -1)
			break;
		
		if (line[0] == '\n') /* enter case */
			continue;

		size = 1, i = 0; /* se setea i = 0 para que al volver a itinerar en el while no de problemas ya que queda guardado el valor anteriormente usado de i */

		while(line[i])
		{
			if(line[i] == 32)
			{
				size++;
			}
			i++;
		}
		
		line[i - 1] = '\0'; /* si antes del '\0' siempre hay un '\n' asi que si i - 1 = '\n' esto hace que se iguale a '\0' sacando el '\n' */

		argv = (char **)malloc(sizeof(char *) * size);/* char ** (argv[0] -> "/bin/ls") ya que apunta a un puntero */
		/* va a tener 1 espacio en la memoria de argv para cada palabra  */
		if (!argv)
		{
			perror("malloc fail");
			exit(EXIT_FAILURE);
		}

		argv[0] = strtok(line, " ");
	
		i = 1;

		while(i < size) /* recorrer cada argumento de argv ya que argv contiene los argumentos */
			argv[i++] = strtok(NULL, " ");

		printf("{%s}\n", argv[0]);

		if (strcmp(argv[0], "exit") == 0)
		{
			free(argv);
			exit(0);
		}

		if (strcmp(argv[0], "env") == 0)
			genv();
		else
		{
			comands(argv);
		}

		free(argv);
	}

	return(0);
}

/**
 *ig_ctrlc - manejo de señales
 *
 *@signum: señal
 *
 */
void ig_ctrlc(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 *comands - ejecute comand
 *
 *@argv: argv
 *
 * Return: 0
 */

int comands(char **argv)
{
	char *token;
	pid_t pid;	
	
	token = malloc(sizeof(char *) * strlen(argv[0]) + 6);
	pid = fork();

	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	
	else if (pid == 0)
	{
		if (strchr(argv[0], '/')) /* 1 ya que el string 1 contiene mas chars que unicamente "/" */
			;
		else
		{

			sprintf(token, "/bin/%s", argv[0]); /* le aigno token ya que una variable no se puede asignar asi misma */
			argv[0] = token;

			printf("[%s]\n", argv[0]);
		}

		if (access(argv[0], X_OK) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	return(0);
}
