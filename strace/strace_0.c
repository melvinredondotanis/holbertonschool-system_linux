#include "strace.h"

/**
* main - Entry point
* @argc: The number of arguments
* @argv: The arguments
*
* Return: 0 on success, otherwise 1
*/
int main(int argc, char **argv)
{
	pid_t child_pid;
	int status, syscall_number, print_next_syscall;
	struct user_regs_struct user_registers;

	setvbuf(stdout, NULL, _IONBF, 0);

	child_pid = fork();

	if (child_pid < 0)
		exit(EXIT_FAILURE);
	else if (child_pid == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		argv[argc] = NULL;
		execvp(argv[1], argv + 1);
	}
	else
	{
		wait(&status);
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		for (print_next_syscall = 0; !WIFEXITED(status); print_next_syscall ^= 1)
		{
			wait(&status);
			ptrace(PTRACE_GETREGS, child_pid, 0, &user_registers);
			if (print_next_syscall)
			{
				syscall_number = user_registers.orig_rax;
				printf("%d\n", syscall_number);
			}

			ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		}
	}
	return (0);
}
