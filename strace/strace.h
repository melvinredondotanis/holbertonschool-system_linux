#ifndef __STRACE_H__
#define __STRACE_H__

#include "syscalls.h"

#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern char **environ;

#endif /* __STRACE_H__ */
