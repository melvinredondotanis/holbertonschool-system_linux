#include "signals.h"

/**
 * current_handler_sigaction - Retrieves current handler of the signal SIGINT
 *
 * Return: pointer to current SIGINT handler, or NULL on failure
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction oldact;

	return (sigaction(SIGINT, NULL, &oldact) ? NULL : oldact.sa_handler);
}
