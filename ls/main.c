#include "hls.h"

/**
 * main - Main function of hls
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	DIR *dir;
	struct dirent *read;

	dir = opendir(".");
	if (dir == NULL)
		return (1);

	while ((read = readdir(dir)) != NULL)
	{
		if (_strcmp(read->d_name, ".") == 0 || _strcmp(read->d_name, "..") == 0)
			continue;
		printf("%s\n", read->d_name);
	}
	closedir(dir);

	return (0);
}
