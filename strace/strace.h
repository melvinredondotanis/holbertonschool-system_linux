#ifndef _STRACE_H_
#define _STRACE_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

#include "syscalls.h"

extern char **environ;

#endif /* _STRACE_H_ */
