#include "hls.h"

/**
 * _memcpy - copies memory
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
		dest[i] = src[i];

	return (dest);
}

/**
 * cleanup - frees memory
 * @entries: pointer to content entries
 * @dirs: pointer to content directories
 * @opt: pointer to options struct
 */
void cleanup(content *entries, content *dirs, option *opt)
{
	if (entries)
		free(entries);
	if (dirs)
		free(dirs);
	if (opt)
		free(opt);
}
