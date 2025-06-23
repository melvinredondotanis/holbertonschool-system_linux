#include "signals.h"

/**
 * siginthandler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
void siginthandler(int signum)
{
	printf("Caught %d\n", signum);
}

/**
 * main - Sets handler for SIGINT and exits after signal received and handled
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	struct sigaction act;

	act.sa_handler = siginthandler;
	sigaction(SIGINT, &act, NULL);
	pause();
	puts("Signal received");
	return (EXIT_SUCCESS);
}
