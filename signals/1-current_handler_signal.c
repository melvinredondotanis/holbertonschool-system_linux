#include "signals.h"

/**
 * current_handler_signal - Retrieves current handler of the signal SIGINT
 *
 * Return: pointer to current SIGINT handler, or NULL on failure
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = signal(SIGINT, SIG_DFL);

	return (signal(SIGINT, handler) == SIG_ERR ? NULL : handler);
}
