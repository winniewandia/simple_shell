#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
	pid_t child1, child2, child3, child4, child5;
	int status1, status2, status3, status4, status5;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	child1 = fork();
	if (child1 ==  -1)
	{
		perror("error");
		return (1);
	}
	if (child1 == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
        {
                perror("error");
        }
		printf("first child");
		sleep(3);
	}
	else 
	{
		wait(&status1);
		printf("parent");
	}
	child2 = fork();
	if (child2 == -1)
	{
		perror("error");
		return (1);
	}
	if (child2 == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
        {
                perror("error");
        }
		printf("second child");
		sleep(3);
	}
	else
	{
		wait(&status2);
		printf("parent");
	}
	child3 = fork();
	if (child3 == -1)
	{
		perror("error");
		return (1);
	}
	if (child3 == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
        {
                perror("error");
        }
		printf("third child");
		sleep(3);
	}
	else
	{
		wait(&status3);
		printf("parent");
	}
	child4 = fork();
	if (child4 == -1)
	{
		perror("error");
		return (1);
	}
	if (child4 == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
        {
                perror("error");
        }
		printf("fourth child");
		sleep(3);
	}
	else
	{
		wait(&status4);
		printf("parent");
	}
	child5 = fork();
	if (child5 == -1)
	{
		perror("error");
		return (1);
	}
	if (child5 == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
        {
                perror("error");
        }
		printf("fifth child");
		sleep(3);
	}
	else
	{
		wait(&status5);
		printf("parent");
	}
	return (0);
}


