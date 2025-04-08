#include "laps.h"

/**
 * create_cars_node - creates a new car node
 * @id: id of the car
 * Return: pointer to the new car node
 */
cars *create_cars_node(int id)
{
	cars *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->id = id;
	new->laps = 0;
	new->next = NULL;
	return (new);
}

/**
 * add_cars - adds a new car node to the linked list
 * @head: pointer to the head of the linked list
 * @new: pointer to the new car node
 */
void add_cars(cars **head, cars *new)
{
	cars **current;

	current = head;
	while (*current && new->id > (*current)->id)
		current = &(*current)->next;
	new->next = *current;
	*current = new;
}

/**
 * print_state - print in the format "Car <id> [<laps> laps]"
 * @head: pointer to the head of the linked list
 */
void print_state(cars **head)
{
	cars **current;

	printf("Race state:\n");
	current = head;
	while (*current)
	{
		printf("Car %i [%lu laps]\n", (*current)->id, (*current)->laps);
		current = &(*current)->next;
	}
}

/**
 * check_cars - check if car id exists and update laps or add new car
 * @head: pointer to the head of the linked list
 * @id: array of car ids
 * @size: size of the id array
 */
void check_cars(cars **head, int *id, size_t size)
{
	cars **current;
	size_t i;

	for (i = 0; i < size; ++i)
	{
		for (current = head; *current; current = &(*current)->next)
			if (id[i] == (*current)->id)
			{
				++(*current)->laps;
				break;
			}
		if (!*current)
		{
			printf("Car %i joined the race\n", id[i]);
			add_cars(head, create_cars_node(id[i]));
		}
	}
}

/**
 * race_state - keeps track of the state of a car race
 * @id: array of car ids
 * @size: size of the id array
 */
void race_state(int *id, size_t size)
{
	static cars *head;
	cars *current;

	current = head;
	if (size)
	{
		check_cars(&head, id, size);
		print_state(&head);
	}
	else
	{
		while (current)
		{
			current = current->next;
			free(head);
			head = current;
		}
	}
}
