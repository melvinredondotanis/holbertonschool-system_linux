#include <pthread.h>
#include <stdio.h>
#include "multithreading.h"

/**
 * thread_entry - ...
 * @arg: ...
 *
 * Return: ...
 */
void *thread_entry(void *arg)
{
	if (!arg)
		pthread_exit(&arg);

	printf("%s\n", (char *) arg);
	pthread_exit(NULL);
}
