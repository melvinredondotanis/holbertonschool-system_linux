#include <signal.h>
#include <sys/types.h>

/**
 * pid_exist - Tests if a process exists
 * @pid: process id to test
 *
 * Return: 1 if exists, otherwise 0
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) + 1);
}
