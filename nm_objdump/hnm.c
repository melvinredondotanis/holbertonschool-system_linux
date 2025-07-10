#include "hnm.h"

/**
 * main - Entry point for the hnm program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(int argc, char **argv)
{
	int status = EXIT_SUCCESS;
	char **_argv = argv;

	if (argc < 2)
		return (fprintf(stderr, USAGE), EXIT_FAILURE);
	while (*++_argv)
	{
		if (argc > 2)
			printf("\n%s:\n", *_argv);
		status = displays_symbols(*_argv, argv[0]);
	}
	return (status);
}
