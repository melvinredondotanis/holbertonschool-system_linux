#include "strace.h"

#define ENOSYS_ERROR -38

/**
* print_params - prints the parameters of a syscall
* @regs: struct containing the registers of the process
*/
void print_params(struct user_regs_struct *regs)
{
	size_t i;
	unsigned long param;
	syscall_t syscall = syscalls_64[regs->orig_rax];

	if (!regs)
		return;

	for (i = 0; i < syscall.nb_params; i++)
	{
		if (syscall.params[i] == VOID)
			continue;

		switch (i)
		{
		case 0:
			param = (unsigned long)regs->rdi;
			break;
		case 1:
			param = (unsigned long)regs->rsi;
			break;
		case 2:
			param = (unsigned long)regs->rdx;
			break;
		case 3:
			param = (unsigned long)regs->r10;
			break;
		case 4:
			param = (unsigned long)regs->r8;
			break;
		case 5:
			param = (unsigned long)regs->r9;
			break;
		default:
			return;
		}
		if (syscall.params[i] == VARARGS)
			printf("...");
		else
			printf("%#lx%s", param, (i < syscall.nb_params - 1) ? ", " : "");
	}
}


/**
* createTracedProcess - creates a traced process
* @argv: arguments to be passed to the process
*
* Return: PID of the created process
*/
pid_t createTracedProcess(char **argv)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		raise(SIGSTOP);
		execvp(argv[0], argv);
		perror("execvp");
		exit(EXIT_FAILURE);
	}

	return (child_pid);
}

/**
* traceSyscalls - traces the syscalls of a process
* @child_pid: PID of the process to be traced
*/
void traceSyscalls(pid_t child_pid)
{
	int status, syscall_number, print_syscall_name, call_count = 0;
	struct user_regs_struct user_registers;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SYSCALL, child_pid, 0, 0);

	for (print_syscall_name = 0; !WIFEXITED(status); print_syscall_name ^= 1)
	{
		ptrace(PTRACE_GETREGS, child_pid, 0, &user_registers);

		if (!print_syscall_name && call_count)
		{
			syscall_number = user_registers.orig_rax;
			printf("%s(", syscalls_64[syscall_number].name);
			print_params(&user_registers);
		}

		if (print_syscall_name && (long)user_registers.rax != ENOSYS_ERROR
			&& call_count)
		{
			printf(") = %s%lx\n", user_registers.rax ? "0x" : "",
					(long)user_registers.rax);
		}

		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		waitpid(child_pid, &status, 0);
		call_count = 1;
	}
}


/**
* main - entry point
* @argc: number of arguments
* @argv: arguments
*
* Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int main(int argc, char **argv)
{
	pid_t child_pid;

	setvbuf(stdout, NULL, _IONBF, 0);

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	child_pid = createTracedProcess(argv + 1);
	traceSyscalls(child_pid);

	printf(") = ?\n");
	return (EXIT_SUCCESS);
}
