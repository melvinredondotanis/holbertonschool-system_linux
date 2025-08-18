#include "strace.h"

/**
* print_syscall_name - print the name of the system call
* @regs: structure containing the registers
*/
void print_syscall_name(struct user_regs_struct regs)
{
	printf("%s", (char *)syscalls_64[(unsigned long)regs.orig_rax].name);
}

/**
* trace_child - trace the child process
* @child: PID of the child process
*/
void trace_child(pid_t child)
{
	int retval, flag = 0;
	struct user_regs_struct regs;

	while (wait(&retval) && !WIFEXITED(retval))
	{
		if (flag)
			printf("\n"), flag = 0;
		memset(&regs, 0, sizeof(regs));
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		if (WSTOPSIG(retval) == SIGTRAP && (long)regs.rax == -38)
		{
			print_syscall_name(regs);
			flag = 1;
		}
		ptrace(PTRACE_SYSCALL, child, 0, 0);
	}
	printf("\n");
}

/**
* execute_traced_command - execute a traced command
* @argv: argument vector
* @envp: env string array
* Return: 0 success, 1 on failure
*/
int execute_traced_command(char *argv[], char *envp[])
{
	pid_t child;
	int retval = 0;

	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		execve(argv[0], argv, envp);
	}
	else
	{
		wait(&retval);
		if (WIFEXITED(retval))
			return (0);
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		trace_child(child);
	}
	return (0);
}

/**
* main - executes a traced command given in argv[1]
* @argc: argument count
* @argv: argument vector
* @envp: env string array
* Return: 0 success, 1 on failure
*/
int main(int argc, char *argv[], char *envp[])
{
	if (argc < 2)
		return (fprintf(stderr, "Bad usage dude\n"), 1);

	setbuf(stdout, NULL);

	return (execute_traced_command(argv + 1, envp));
}

