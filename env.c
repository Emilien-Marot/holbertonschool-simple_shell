#include "shell.h"

/**
 * _getenv - function to get the environemental variable
 * with the name given in parameter
 *
 * @name: name of the environemental variable to get
 *
 * Return: a string containing a copy of the variable
 * (NULL if the variable does not exist)
 */
char *_getenv(const char *name)
{
	int i, j, same;

	if(environ == NULL)
		return(NULL);
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
			return(strdup(&(environ[i][j+1])));
		}
	}
	return(NULL);
}

/**
 * print_env - print line by line the environemental variables
 */
void print_env()
{
	int i;

	if(environ == NULL)
		return;
	for(i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * get_path - function that looks for the path to the desired command
 *
 * @name: command to look for
 *
 * Return: the full path to the command (NULL if the command does not exist)
 */
char *get_path(char *name)
{
	char *PATH, *path, *full;
	int i, j;

	if (name == NULL)
		return(NULL);
	if(access(name, F_OK) == 0)
	{
		return(strdup(name));
	}
	PATH = _getenv("PATH");
	if(PATH == NULL)
		return(NULL);
	full = malloc(PATH_MAX * sizeof(char));
	if(full == NULL)
	{
		free(PATH);
		return(NULL);
	}
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
			free(PATH);
			return(full);
		}
		path = strtok(NULL, ":");
	}
	free(PATH);
	free(full);
	return(NULL);
}
