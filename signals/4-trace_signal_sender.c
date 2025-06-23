#include "signals.h"

/**
 * sigquithandler - action to take on SIGQUIT intercept
 * @sig: number of the signal that caused invocation of the handler
 * @info: pointer to a siginfo_t
 * @ucontext: pointer to a ucontext_t
 */
void sigquithandler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	printf("SIGQUIT sent by %i\n", info->si_pid);
	fflush(stdout);
}

/**
 * trace_signal_sender - Defines a handler for SIGQUIT
 *
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sigquithandler;
	return (sigaction(SIGQUIT, &act, NULL));
}
