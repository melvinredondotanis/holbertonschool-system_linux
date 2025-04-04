#include "hls.h"

/**
 * _strlen - Function to calculate the length of a string.
 * @str: The string to calculate the length of.
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}

/**
* _strcpy - Function to copy a string from source to destination.
* @dest: The destination string.
* @src: The source string.
* Return: A pointer to the destination string.
*/
char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while ((*dest++ = *src++))
		;

	return (dest_start);
}
