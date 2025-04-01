#include "hls.h"

/**
 * main - Entry point for the program
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 *
 * Return: 0 on success, error will exit with value of 2
 */
int main(int argc, char **argv)
{
	short status;
	(void) argc;

	status = 0;
	status = ls(argv);
	return (status);
}
