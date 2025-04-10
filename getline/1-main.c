#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
	int fd;
	char *line;

	fd = open("1-main.c", 0);
	while ((line = _getline(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}