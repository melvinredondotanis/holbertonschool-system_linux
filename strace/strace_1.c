#include "strace.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void trace_child(char **av, char **envp);
void trace_parent(pid_t child_pid);
int await_syscall(pid_t child_pid);

/**
 * main - entry point
 */
int main(int ac, char **av, char **envp)
{
	pid_t child_pid;

	if (ac < 2)
	{
		printf("Usage: %s command [args...]\n", av[0]);
		return (EXIT_FAILURE);
	}
	setbuf(stdout, NULL);
	child_pid = fork();
	if (child_pid == -1)
	{
		dprintf(STDERR_FILENO, "Fork failed: %d\n", errno);
		return (EXIT_FAILURE);
	}
	else if (child_pid == 0)
		trace_child(av, envp);
	else
		trace_parent(child_pid);
	return (0);
}

/**
 * trace_child - traces child process
 */
void trace_child(char **av, char **envp)
{
	if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
	{
		dprintf(STDERR_FILENO, "PTRACE_TRACEME failed: %d\n", errno);
		_exit(1);
	}
	kill(getpid(), SIGSTOP);
	if (execve(av[1], av + 1, envp) == -1)
	{
		dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
		_exit(1);
	}
}

/**
 * trace_parent - calls made by tracing parent
 */
void trace_parent(pid_t child_pid)
{
	int status;
	struct user_regs_struct uregs;
	int entering = 1;

	if (waitpid(child_pid, &status, 0) == -1)
		return;
	if (ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD) == -1)
		return;

	while (1)
	{
		if (await_syscall(child_pid))
			break;

		memset(&uregs, 0, sizeof(uregs));
		if (ptrace(PTRACE_GETREGS, child_pid, 0, &uregs) == -1)
			break;

		if (entering)
			printf("%s\n", syscalls_64_g[uregs.orig_rax].name);

		entering = !entering;
	}
	printf("\n");
}

/**
 * await_syscall - waits for next syscall stop
 */
int await_syscall(pid_t child_pid)
{
	int status;

	while (1)
	{
		if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) == -1)
			return (1);
		if (waitpid(child_pid, &status, 0) == -1)
			return (1);
		if (WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80))
			return (0);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return (1);
	}
}
