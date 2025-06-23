#include "signals.h"

/**
 * siginthandler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
void siginthandler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - Sets a handler for SIGINT
 *
 * Return: 1 on success, -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;

	act.sa_handler = siginthandler;
	return (sigaction(SIGINT, &act, NULL));
}
