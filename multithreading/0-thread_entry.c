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
	printf("%s\n", (char *) arg);
	return (NULL);
}
