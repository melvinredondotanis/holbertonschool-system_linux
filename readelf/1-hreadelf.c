#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: Always 0 (Success) or -1 (Failure)
 */
int main(int argc, char **argv, char **env)
{
	(void)argc;
	char *av[] = {"/usr/bin/readelf", "-W", "-S", "", NULL};

	av[3] = argv[1];
	if (execve("/usr/bin/readelf", av, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
