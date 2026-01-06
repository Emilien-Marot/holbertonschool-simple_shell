#include <stdio.h>
#include <stdlib.h>
#include<string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int i, j, same;

	for(i = 0; environ[i] != NULL; i++)
	{
		same = 1;
		for(j = 0; name[j] != '\0'; j++)
		{
			if(environ[i][j] != name[j])
			{
				same = 0;
				break;
			}
		}
		if(same && environ[i][j] == '=' && name[j] == '\0')
		{
			return(&(environ[i][j+1]));
		}
	}
	return(NULL);
}

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main()
{
	const char *name = "PATH";
	const char *env_1 = getenv(name);
	if(env_1)
	{
		printf("Your %s is %s\n", name, env_1);
	}
	const char *env_2 = _getenv(name);
	if(env_2)
	{
		printf("Your %s is %s\n", name, env_2);
	}
	return (0);
}
