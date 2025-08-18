#ifndef __STRACE_H__
#define __STRACE_H__

#include "syscalls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <limits.h>
#include <errno.h>

extern char **environ;
#define ENOSYS_ERROR -38
#define CHAR_PTR 6

/*Functions fors Task 1 */
void print_syscall_name(struct user_regs_struct regs);
void trace_child(pid_t child);
int execute_traced_command(char *argv[], char *envp[]);

/*Functions fors Task 2 and 3 */
void print_params(struct user_regs_struct *regs);
/* void traceSyscalls(pid_t child_pid); */
pid_t createTracedProcess(char **argv);

void traceSyscalls(pid_t child_pid, char **argv);
#endif /* __STRACE_H__ */
