#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *path, *pathcopy, *token, *filename;
	int i;
	struct stat filestat;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("Path error");
		return (1);
	}
	pathcopy = strdup(path);
	if (pathcopy == NULL)
	{
		printf("Pathcopy error");
		return (1);
	}
	token = strtok(pathcopy, ":");
	while (token != NULL)
	{
		for (i = 1; i < argc; i++)
		{
			filename = argv[i];
			char filepath[256];
			snprintf(filepath, sizeof(filepath), "%s/%s", token, filename);
			if (stat(filepath, &filestat) == 0 && S_ISREG(filestat.st_mode))
			{
				printf("%s\n", filepath);
			}
		}
		token = strtok(NULL, ":");
	}
	free(pathcopy);
	return (0);
}

