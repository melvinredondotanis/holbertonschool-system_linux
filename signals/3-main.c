#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
void print_hello(int signum)
{
	(void) signum;
	puts("Hello :)");
}

void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	void (*handler)(int);
	int i;

	handler = current_handler_sigaction();
	printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

	/* Set 'print_hello()` as the handler for SIGINT */
	set_print_hello();

	handler = current_handler_sigaction();
	printf("Address of the 'print_hello' function: %#lx\n", (unsigned long int)&print_hello);
	printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

	for (i = 0; ; i++)
	{
		printf("[%d] Wait for it ...\n", i);
		sleep(1);
	}
	return (EXIT_SUCCESS);
}
