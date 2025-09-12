#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

#define NB_THREADS 10

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused)) void *arg)
{
	tprintf("Hello from thread\n");
	return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	pthread_t tid[NB_THREADS];
	int i;

	for (i = 0; i < NB_THREADS; i++)
		pthread_create(&tid[i], NULL, &_thread_entry, NULL);

	tprintf("Hello from main thread\n");

	for (i = 0; i < NB_THREADS; i++)
		pthread_join(tid[i], NULL);

	return (EXIT_SUCCESS);
}
