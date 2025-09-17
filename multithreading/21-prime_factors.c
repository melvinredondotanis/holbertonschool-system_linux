#include "multithreading.h"
#include "list.h"
#include <stdlib.h>

void free_list(list_t *list);

/**
 * add_to_list - program that adds an element to the end of the linked list
 *
 * this function appends an unsigned long integer to the linked list
 *
 * @list: a pointer to the 'list_t' structure representing the linked list
 * @factor: the unsigned long integer to be added to the list
 *
 * Return: 1 if the addition is successful, 0 otherwise
 */

int add_to_list(list_t *list, unsigned long factor)
{
	unsigned long *content;
	node_t *new_node;

	content = malloc(sizeof(*content));

	if (!content)
		return (0);

	*content = factor;
	new_node = malloc(sizeof(*new_node));

	if (!new_node)
	{
		free(content);
		return (0);
	}

	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = list->tail;

	if (list->tail)
	{
		list->tail->next = new_node;
	}
	else
	{
		list->head = new_node;
	}

	list->tail = new_node;
	list->size++;

	return (1);
}

/**
 * prime_factors - program that calculates the prime factors of an input number
 * represented as a string
 *
 * this function takes a string containing a numeric value, converts it to an
 * unsigned long integer, and returns a linked list of its prime factors
 *
 * @s: a pointer to a character array representing the input number
 *
 * Return: a pointer to a 'list_t' structure containing the prime factors,
 *         or NULL if an error occurs
 */

list_t *prime_factors(char const *s)
{
	unsigned long n = strtoul(s, NULL, 10);
	unsigned long i;
	list_t *factors = malloc(sizeof(*factors));

	if (!factors)
		return (NULL);

	factors->head = NULL;
	factors->tail = NULL;
	factors->size = 0;

	/* Factorize */
	for (i = 2; i <= n / i; i++)
	{
		while (n % i == 0)
		{
			if (!add_to_list(factors, i))
			{
				free_list(factors);
				return (NULL);
			}
			n /= i;
		}
	}
	if (n > 1)
	{
		if (!add_to_list(factors, n))
		{
			free_list(factors);
			return (NULL);
		}
	}

	return (factors);
}

/**
 * free_list - program that frees the memory occupied by a linked list
 * and its contents
 *
 * this function takes a pointer to a 'list_t' structure and deallocates
 * all memory used by the linked list and its elements
 *
 * @list: a pointer to the 'list_t' structure representing the linked list
 *
 * Return: nothing (void)
 */

void free_list(list_t *list)
{
	node_t *current = list->head;
	node_t *next;

	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(list);
}
