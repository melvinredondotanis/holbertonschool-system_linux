#include "signals.h"

/**
 * sigint_handler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
void sigint_handler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - sets a handler for the signal SIGINT
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	return (signal(SIGINT, sigint_handler) == SIG_ERR ? -1 : 0);
}
