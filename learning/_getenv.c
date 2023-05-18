#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
char *_getenv(const char *name)
{
	int len, i;
	
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=' )
		{
			return (&environ[i][len + 1]);
		}
	}
	return (NULL);
}
int main(void)
{
	char *value;

	value = _getenv("PATH");
	printf("%s\n", value);
}

