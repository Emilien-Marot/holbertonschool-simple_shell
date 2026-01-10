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

	if (environ == NULL)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		same = 1;
		for (j = 0; name[j] != '\0'; j++)
		{
			if (environ[i][j] != name[j])
			{
				same = 0;
				break;
			}
		}
		if (same && environ[i][j] == '=' && name[j] == '\0')
		{
			return (strdup(&(environ[i][j + 1])));
		}
	}
	return (NULL);
}

/**
 * print_env - print line by line the environemental variables
 */
void print_env(void)
{
	int i;

	if (environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * get_path_loop - check all the paths in the
 * environemental variable PATH to find the one to the command desired
 *
 * @name: name of the command to look for
 * @paths: string of all paths separated by ":"
 * @full: string to store the full path
 */
void get_path_loop(char *name, char *paths, char *full)
{
	char *path;
	int i, j;

	path = strtok(paths, ":");
	while (path != NULL)
	{
		i = 0;
		full[0] = '\0';
		while (path[i] != '\0')
		{
			full[i] = path[i];
			i++;
			full[i] = '\0';
		}
		full[i] = '/';
		i++;
		full[i] = '\0';
		j = 0;
		while (name[j] != '\0')
		{
			full[i + j] = name[j];
			j++;
			full[i + j] = '\0';
		}
		if (access(full, F_OK) == 0)
		{
			return;
		}
		path = strtok(NULL, ":");
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
	char *paths, *full;

	if (name == NULL)
		return (NULL);
	if (access(name, F_OK) == 0)
	{
		return (strdup(name));
	}
	paths = _getenv("PATH");
	if (paths == NULL)
		return (NULL);
	full = malloc(PATH_MAX * sizeof(char));
	if (full == NULL)
	{
		free(paths);
		return (NULL);
	}
	get_path_loop(name, paths, full);
	free(paths);
	if (full != NULL)
		return (full);
	free(full);
	return (NULL);
}
