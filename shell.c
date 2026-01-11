#include "shell.h"

/**
 * l_free - free a list of strings and all the strings it points to
 * 
 * @list_words: list of strings to be freed
 *
 * Return: void
 */
void l_free(char **list_words)
{
	int i = 0;

	for (i = 0; list_words[i] != NULL; i++)
	{
		free(list_words[i]);
		list_words[i] = NULL;
	}
}

/**
 * string_to_list - take a string and separate it into a list of words
 * 
 * @string: string to be converted into a list
 * @list: list that will contain the strings
 *
 * Return: 0 on success, -1 for an error
 */
int string_to_list(char *string, char **list)
{
    int i = 0;

	if (list == NULL)
		return (-1);
	if (string == NULL)
	{
		list[0] = NULL;
		return (0);
	}
	list[0] = strtok(string, "\t\n ");
	while (list[i] != NULL)
	{
	    i++;
	    list[i] = strtok(NULL, "\t\n ");
	}
	return (0);
}

/**
 * prompt - waits for a command from stdin and execute it in a child process
 * 
 * @buffer: buffer that will contain the text from the stdin
 * @list_words: list of strings that will contain the words of the buffer
 *
 * Return: return 1 to continue the loop, 0 to exit the loop and -1 for an error
 */
int prompt(const char *shell_name)
{
	ssize_t res = 0;
	size_t buf_size = 0;
	char *buffer = NULL, *path = NULL;
	pid_t child_pid = 0;
	int status, atty = isatty(0);
	char **list_words = NULL;

	if(atty == 0)
		errno = 0;
	else
		printf("#cisfun$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
	{
		free(buffer);
		if (errno != 0)
			return(-1);
		else if(atty)
			printf("\n");
		return(0);
	}
	list_words = malloc(BUF_SIZE * sizeof(char *));
	if (list_words == NULL)
	{
		free(buffer);
		return (-1);
	}
	list_words[0] = NULL;
	if (string_to_list(buffer, list_words) == -1)
	{
		free(buffer);
		return(-1);
	}
	if (list_words[0] == NULL)
	{
		free(buffer);
		free(list_words);
		return(1);
	}
	if (strcmp(list_words[0], "exit") == 0)
	{
		free(buffer);
		free(list_words);
		return(0);
	}
	if(strcmp(list_words[0], "env") == 0)
	{
		print_env();
		free(buffer);
		free(list_words);
		return(1);
	}
	path = get_path(list_words[0]);
	if (path == NULL)
	{
		errno = 0;
		fprintf(stderr, "%s: 1: %s: not found\n", shell_name, list_words[0]);
		free(buffer);
		free(list_words);
		exit(127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free(path);
		free(buffer);
		free(list_words);
		return(-1);
	}
	if (child_pid == 0)
	{
		if (execve(path, list_words, NULL) == -1)
			return(-1);
		return(-1);
	}
	else
	{
		wait(&status);
		free(path);
		free(buffer);
		free(list_words);
		return(1);
	}
}

/**
 * main - program to run a simple shell
 * 
 * @ac: number of arguments given
 * @av: list of arguments given
 *
 * Return: return 0 if it worked and 1 for an error
 */
int main(int ac __attribute__((unused)), char **av)
{
	int ret = 0;
	const char *name = av[0];

	while (1) {
		ret = prompt(name);
		if(ret == -1)
			perror(name);
		if (ret != 1)
			break;
	}
	if(ret == -1)
		return (errno);
	fprintf(stderr, "%s", "");
	return(0);
}
