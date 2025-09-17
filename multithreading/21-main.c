#include <stdlib.h>
#include <stdio.h>
#include "multithreading.h"

/**
 * print_factors - Print a nmber and its prime factorization
 *
 * @s:       Number as string
 * @factors: List of prime factors
 */
static void print_factors(char const *s, list_t const *factors)
{
	node_t const *factor;

	printf("%s =", s);
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
	size_t i;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s n\n", av[0]);
		return (EXIT_FAILURE);
	}

	for (i = 1; i < (size_t)ac; i++)
	{
		list_t *factors;

		factors = prime_factors(av[i]);
		print_factors(av[i], factors);
		list_destroy(factors, free);
		free(factors);
	}

	return (EXIT_SUCCESS);
}
