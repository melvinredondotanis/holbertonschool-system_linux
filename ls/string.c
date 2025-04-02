#include "hls.h"

/**
 * _memcpy - Copies memory area
 * @dest: Pointer to destination memory area
 * @src: Pointer to source memory area
 * @n: Number of bytes to copy
 *
 * Return: Pointer to destination memory area
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;

	while (n--)
		*d++ = *s++;

	return (dest);
}

/**
 * _strlen - Gets the length of a string
 * @s: The string to measure
 *
 * Return: The length of the string
 */
size_t _strlen(const char *s)
{
	size_t len = 0;

	while (*s++)
		len++;

	return (len);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string to compare
 * @s2: Second string to compare
 *
 * Return: Negative if s1 < s2, 0 if s1 == s2, positive if s1 > s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcpy - Copies a string to another
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';

	return (ptr);
}

/**
 * str_toupper - Converts a string to uppercase
 * @str: The string to convert
 *
 * Return: Pointer to the converted string
 */
char *str_toupper(char *str)
{
	char *ptr = str;

	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 32;
		str++;
	}

	return (ptr);
}
