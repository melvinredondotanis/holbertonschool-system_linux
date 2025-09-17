#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "multithreading.h"

#define NB_THREADS 8

/**
 * print_task_result - Print the result of a task
 *
 * @task: Pointer to the task to print the result of
 */
void print_task_result(task_t *task)
{

	list_t *factors = (list_t *)task->result;
	node_t *factor;

	printf("%s =", (char *)task->param);
	for (factor = factors->head; factor; factor = factor->next)
	{
		unsigned long n = *((unsigned long *)factor->content);

		printf("%s %lu", factor->prev ? " *" : "", n);
	}
	printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments count
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
	list_t tasks;
	pthread_t threads[NB_THREADS];
	size_t i;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s n\n", av[0]);
		return (EXIT_FAILURE);
	}

	if (!list_init(&tasks))
		return (EXIT_FAILURE);

	for (i = 1; i < (size_t)ac; i++)
		list_add(&tasks,
				 create_task((task_entry_t)prime_factors, av[i]));

	printf("Executing %lu tasks on %u threads\n", tasks.size, NB_THREADS);

	for (i = 0; i < NB_THREADS; i++)
		pthread_create(&threads[i], NULL,
					   (void *(*)(void *))exec_tasks, &tasks);
	for (i = 0; i < NB_THREADS; i++)
		pthread_join(threads[i], NULL);

	list_each(&tasks, (node_func_t)print_task_result);

	list_destroy(&tasks, (node_func_t)destroy_task);

	return (EXIT_SUCCESS);
}
