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
 * @ac: argument count
 * @av: argument vector
 * @envp: environ
 * Return: EXIT_SUCCESS or error.
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
		exit(EXIT_FAILURE);
	}
	else if (!child_pid)
		trace_child(av, envp);
	else
		trace_parent(child_pid);
	return (0);
}

/**
 * trace_child - traces child process
 * @av: argument vector for execve
 * @envp: environ for execve
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
 * @child_pid: pid of child to trace
 */
void trace_parent(pid_t child_pid)
{
	int status;
	struct user_regs_struct uregs;

	if (waitpid(child_pid, &status, 0) == -1)
		return;
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		if (ptrace(PTRACE_GETREGS, child_pid, 0, &uregs) == -1)
			break;
		printf("%ld\n", (long)uregs.orig_rax);
		if (await_syscall(child_pid))
			break;
	}
}

/**
 * await_syscall - waits for a syscall
 * @child_pid: pid of process to await
 * Return: 0 if child stopped, 1 if exited
 */
int await_syscall(pid_t child_pid)
{
	int status;

	while (1)
	{
		if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) == -1)
			return 1;
		if (waitpid(child_pid, &status, 0) == -1)
			return 1;
		if (WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80))
			return 0;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			return 1;
	}
}
