#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "multithreading.h"

void mutex_init(void) __attribute__((constructor));
void mutex_destroy(void) __attribute__((destructor));
static pthread_mutex_t mutex;

/**
 * mutex_init - ...
 */
void mutex_init(void)
{
	if (pthread_mutex_init(&mutex, NULL) != 0)
		exit(EXIT_FAILURE);
}

/**
 * mutex_destroy - ...
 */
void mutex_destroy(void)
{
	if (pthread_mutex_destroy(&mutex) != 0)
		exit(EXIT_FAILURE);
}

/**
 * tprintf - ...
 * @format: ...
 * Return: ...
 */
int tprintf(char const *format, ...)
{
	int status = 0;
	va_list args;

	if (!format)
		return (-1);

	pthread_mutex_lock(&mutex);

	printf("[%lu] ", pthread_self());
	va_start(args, format);
	status = vprintf(format, args);
	va_end(args);

	pthread_mutex_unlock(&mutex);
	return (status);
}
