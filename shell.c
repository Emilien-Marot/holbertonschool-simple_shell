#include "shell.h"

#define BUF_SIZE 1024

/**
 * l_free - free a list of strings and all the strings it points to
 * 
 * @list_words: list of strings to be freed
 *
 * Return: void
 */
void l_free(char **list_words)
{
	int i;

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

	if (list == NULL || string == NULL)
		return (-1);
	list[0] = strtok(string, "\t\n ");
	while (list[i] != NULL)
	{
	    printf("%s\n", list[i]);
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
int prompt(char **list_words)
{
	ssize_t res;
	size_t buf_size = 0;
	char *buffer = NULL;
	pid_t child_pid;
	int status, atty = isatty(0);

	if(atty == 0)
		errno = 0;
	else
		printf("#cisfun$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
	{
		free(buffer);
		if (errno != 0)
			return(2);
		else if(atty)
			printf("\n");
		return(0);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		free(buffer);
		return(3);
	}
	if (child_pid == 0)
	{
		if (string_to_list(buffer, list_words) == -1)
		{
			free(buffer);
			return(4);
		}
		if (execve(list_words[0], list_words, NULL) == -1)
			return(5);
		return(6);
	}
	else
	{
		wait(&status);
		free(buffer);
		return(7);
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
	char **list_words = NULL;
	const char *error = av[0];

	list_words = malloc(BUF_SIZE * sizeof(char *));
	if (list_words == NULL)
	{
		perror(error);
		return (1);
	}
	while (1) {
		ret = prompt(list_words);
		if(ret != 0 && ret != 1)
			perror(error);
		if (ret != 1)
			break;
	}
	l_free(list_words);
	free(list_words);
	return (ret);
}
