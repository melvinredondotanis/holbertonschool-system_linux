#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

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
	pthread_t tid;

	pthread_create(&tid, NULL, &_thread_entry, NULL);
	pthread_join(tid, NULL);

	tprintf("Hello from main thread\n");

	return (EXIT_SUCCESS);
}
