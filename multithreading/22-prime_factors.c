#include "multithreading.h"

static pthread_mutex_t task_status_mutex;

/**
 * initTaskStatusMutex - program that initializes the mutex
 * used to manage access to the status of tasks
 *
 * Return: nothing (void)
 */

void initTaskStatusMutex(void)
{
	pthread_mutex_init(&task_status_mutex, NULL);
}

/**
 * destroyTaskStatusMutex - program that destroys the mutex
 * that was used to manage task statuses
 *
 * Return: nothing (void)
 */

void destroyTaskStatusMutex(void)
{
	pthread_mutex_destroy(&task_status_mutex);
}

/**
 * create_task - program that creates a new task with a specific
 * entry function and parameter
 *
 * @entry: a function pointer to the task function to be executed
 * @param: a pointer to the parameter to be passed to the task function
 *
 * Return: a pointer to the newly created task structure,
 *         or NULL if the creation fails
 */

task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = NULL;

	if (!entry)
		return (NULL);

	task = malloc(sizeof(task_t));

	if (!task)
		return (NULL);

	task->entry = entry;
	task->param = param;
	task->status = PENDING; /* Initial status is set to PENDING */
	task->result = NULL;
	task->lock = task_status_mutex;

	return (task);
}

/**
 * destroy_task - program that destroys a task structure and frees
 * its associated resources
 *
 * @task: a pointer to the task structure to be destroyed
 *
 * Return: nothing (void)
 */

void destroy_task(task_t *task)
{
	if (!task)
		return;

	if (task->result)
	{
		list_destroy(task->result, free);
		free(task->result);
	}

	free(task);
}

/**
 * exec_tasks - program that executes all tasks in a given list,
 * managing each task's state
 *
 * @tasks: a pointer to a list of tasks to be executed
 *
 * Return: NULL always (used for compatibility with threading functions)
 */

void *exec_tasks(list_t const *tasks)
{
	node_t *curr_node = NULL;
	task_t *task = NULL;
	size_t i;

	if (!tasks || !tasks->head)
		return (NULL);

	for (i = 0, curr_node = tasks->head; i < tasks->size;
		 i++, curr_node = curr_node->next)
	{
		task = (task_t *)curr_node->content;

		if (!task)
			continue;

		pthread_mutex_lock(&task_status_mutex);
		if (task->status == PENDING)
		{
			task->status = STARTED;
			pthread_mutex_unlock(&task_status_mutex);

			tprintf("[%02lu] Started\n", i);
			task->result = task->entry(task->param);

			if (!task->result)
			{
				task->status = FAILURE;
				tprintf("[%02lu] Failure\n", i);
			}
			else
			{
				task->status = SUCCESS;
				tprintf("[%02lu] Success\n", i);
			}
		}
		else
			pthread_mutex_unlock(&task_status_mutex);
	}

	return (NULL);
}
