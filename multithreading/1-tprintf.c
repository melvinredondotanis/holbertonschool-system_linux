#include <pthread.h>
#include <stdio.h>
#include "multithreading.h"

/**
 * tprintf - ...
 * @format: ...
 * Return: ...
 */
int tprintf(char const *format, ...)
{
	if (!format)
		pthread_exit(&format);

	printf("[%lu] %s", pthread_self(), format);
	return (0);
}
