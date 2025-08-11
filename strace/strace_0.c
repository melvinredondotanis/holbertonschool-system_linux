#include "strace.h"

/**
 * main - Entry point for the strace program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (2);
	}

	pid_t child = fork();

	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execv(argv[1], &argv[1]);
		perror("execv");
		exit(1);
	}

	int status, in_syscall = 0;
	struct user_regs_struct regs;

	waitpid(child, &status, 0);
	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			break;

		if (!in_syscall)
		{
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			printf("%lld\n", (long long)regs.orig_rax);
		}
		else
			in_syscall = 0;
	}
	return (0);
}