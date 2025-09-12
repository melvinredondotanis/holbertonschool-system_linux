#include <pthread.h>
#include <stdio.h>
#include "multithreading.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * tprintf - ...
 * @format: ...
 * Return: ...
 */
int tprintf(char const *format, ...)
{
	pthread_mutex_lock(&mutex);
	if (!format)
		pthread_exit(&format);

	printf("[%lu] %s", pthread_self(), format);
	pthread_mutex_unlock(&mutex);
	return (0);
}
