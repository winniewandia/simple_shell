#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */

int main(void)
{
	pid_t mypid, parentpid;

	mypid = getpid();
	printf("%u\n", mypid);
	parentpid = getppid();
	printf("%u\n", parentpid);
	return (0);
}

