#include "hls.h"

/**
 * _strlen - gets length of a string
 * @s: string to count
 *
 * Return: length
 */
size_t _strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;

	return (s1[i] - s2[i]);
}

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; ++i)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * strupper - converts a string to uppercase
 * @s: string to convert
 *
 * Return: pointer to string
 */
char *strupper(char *s)
{
	size_t i;

	for (i = 0; s[i]; ++i)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;

	return (s);
}
