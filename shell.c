#include "shell.h"

#define BUF_SIZE 1024

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
 * prompt_init - convert the input into a
 * list of words and execute built-ins if needed
 *
 * @buffer: input to be converted
 * @list_words: list that will contain the words
 *
 * Return: 2 to execute a command, 1 to just continue the loop,
 * 0 to stop and -1 for an error
 */
int prompt_init(char *buffer, char **list_words)
{
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
		return (-1);
	}
	if (list_words[0] == NULL)
	{
		free(buffer);
		free(list_words);
		return (1);
	}
	if (strcmp(list_words[0], "exit") == 0)
	{
		free(buffer);
		free(list_words);
		return (0);
	}
	if (strcmp(list_words[0], "env") == 0)
	{
		print_env();
		free(buffer);
		free(list_words);
		return (1);
	}
	return (2);
}

/**
 * exec_prompt - finds the path to the command and execute it
 *
 * @buffer: string containing the input
 * @list_words: list of pointers to each word of the input
 *
 * Return: return 1 to continue the loop,
 * 0 to exit the loop and -1 for an error
 */
int exec_prompt(char *buffer, char **list_words)
{
	char *path = NULL;
	int status;
	pid_t child_pid = 0;

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
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(path, list_words, NULL) == -1)
			return (-1);
		return (-1);
	}
	else
	{
		wait(&status);
		free(path);
		free(buffer);
		free(list_words);
		return (1);
	}
}

/**
 * prompt - waits for a command from stdin and execute it in a child process
 *
 * @shell_name: name of the executable
 *
 * Return: return 1 to continue the loop,
 * 0 to exit the loop and -1 for an error
 */
int prompt(const char *shell_name)
{
	ssize_t res = 0;
	size_t buf_size = 0;
	char *buffer = NULL, *path = NULL, **list_words = NULL;
	int atty = isatty(0);

	if (atty == 0)
		errno = 0;
	else
		printf("#cisfun$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
	{
		free(buffer);
		if (errno != 0)
			exit(errno);
		else if (atty)
			printf("\n");
		return (0);
	}
	ret = prompt_init();
	if (ret != 0)
		return (ret);
	return (exec_prompt(buffer, list_words));
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

	while (1)
	{
		ret = prompt(name);
		if (ret == -1)
			perror(name);
		if (ret != 1)
			break;
	}
	if (ret == -1)
		return (errno);
	if (stderr == 0)
		fprintf(stderr, "%s", "");
	return (0);
}
