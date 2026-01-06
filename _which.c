#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

char *_getenv(char **env, const char *name)
{
	int i, j, same;

	for(i = 0; env[i] != NULL; i++)
	{
		same = 1;
		for(j = 0; name[j] != '\0'; j++)
		{
			if(env[i][j] != name[j])
			{
				same = 0;
				break;
			}
		}
		if(same && env[i][j] == '=' && name[j] == '\0')
		{
			return(&(env[i][j+1]));
		}
	}
	return(NULL);
}

int main(int ac, char **av, char **env)
{
	char *PATH, *path, *full, *name;
	int i, j;

	PATH = _getenv(env, "PATH");
	if(ac > 1 && PATH == NULL)
		return(1);
	name = av[1];
	full = malloc(PATH_MAX * sizeof(char));
	if(full == NULL)
		return(1);
	path = strtok(PATH, ":");
	while(path != NULL)
	{
		i = 0;
		full[0] = '\0';
		while(path[i] != '\0')
		{
			full[i] = path[i];
			i++;
			full[i] = '\0';
		}
		full[i] = '/';
		i++;
		full[i] = '\0';
		j = 0;
		while(name[j] != '\0')
		{
			full[i+j] = name[j];
			j++;
			full[i+j] = '\0';
		}
		if(access(full, F_OK) == 0)
		{
			printf("%s\n", full);
			return(0);
		}
		path = strtok(NULL, ":");
	}
	return(0);
}
