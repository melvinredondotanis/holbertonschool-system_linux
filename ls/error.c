#include "hls.h"

/**
 * error - prints error message
 * @arg: argument to print
 * @op: option to print
 * @e: exit status
 * @printed: whether to print a newline
 *
 * Return: 2
 */
int error(char *arg, char op, bool e, bool printed)
{
	char buf[256];

	if (printed)
		printf("\n");

	if (!arg)
		fprintf(stderr, "hls: invalid option -- '%c'\n", op);
	else if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", arg);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", arg);

	if (errno > 0)
		perror(buf);

	if (e)
		exit(2);

	return (2);
}
