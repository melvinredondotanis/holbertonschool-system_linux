#include "signals.h"

/**
 * main - Sends SIGINT to a process using its PID
 * @argc: count of arguments
 * @argv: arguments passed
 *
 * Return: EXIT_SUCCESS on success, otherwise EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", *argv);
		return (EXIT_FAILURE);
	}
	return (abs(kill(atoi(argv[1]), SIGINT)));
}
