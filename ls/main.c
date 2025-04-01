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
	int first_entry;

	dir = opendir(".");
	if (dir == NULL)
		return (1);

	first_entry = 1;
	while ((read = readdir(dir)) != NULL)
	{
		if (_strcmp(read->d_name, ".") == 0 || _strcmp(read->d_name, "..") == 0)
			continue;
		else if (read->d_name[0] == '.')
			continue;

		if (!first_entry)
			printf(" ");
		printf("%s", read->d_name);
		first_entry = 0;
	}
	printf("\n");
	closedir(dir);

	return (0);
}
