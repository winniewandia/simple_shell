#include <stdio.h>
#include <unistd.h>

extern char **environ;
int main(int __attribute__ ((unused)) argc, char __attribute__ ((unused)) **argv, char **env)
{
	int i;
	
	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	printf("%p\n", &env);
	printf("%p\n", &environ);
	
	return (0);
}
