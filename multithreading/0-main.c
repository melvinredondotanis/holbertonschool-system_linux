#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, &thread_entry, "Holberton School");

	sleep(1);
	printf("Created thread ID -> %lu\n", tid);

	thread_entry("C is fun");
	printf("Should not be printed\n");
	return (EXIT_SUCCESS);
}
