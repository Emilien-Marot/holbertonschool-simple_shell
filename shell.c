#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUF_SIZE 1024

void l_free(char **list_words)
{
	int i;

	for (i = 0; list_words[i] != NULL; i++)
	{
		free(list_words[i]);
		list_words[i] = NULL;
	}
	free(list_words);
}

int string_to_list(char *string, char **list)
{
	int i, j = 0, idx_w = 0;
	char *word;

	if (list == NULL || string == NULL)
		return (1);
	word = malloc(BUF_SIZE * sizeof(char));
	if (word == NULL)
		return (1);
	j = 0;
	idx_w = 0;
	word[0] = '\0';
	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == ' ' || string[i] == '\n')
		{
			list[idx_w] = strdup(word);
			if (list[idx_w] == NULL)
			{
				list[idx_w] = NULL;
				l_free(list);
				return (1);
			}
			idx_w++;
			list[idx_w] = NULL;
			j = 0;
		}
		else
		{
			word[j] = string[i];
			j++;
		}
		word[j] = '\0';
	}
	return (0);
}

int prompt(char *buffer, size_t buf_size, char **list_words)
{
	ssize_t res;
	pid_t child_pid;
	int status;
	int atty = isatty(0);

	if(atty == 0)
		errno = 0;
	else
		printf("$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
	{
		if (errno != 0)
			return(-1);
		else if(atty)
			printf("\n");
		return(0);
	}
	if (string_to_list(buffer, list_words) == 1)
	{
		return(-1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		return(-1);
	}
	if (child_pid == 0)
	{
		if (execve(list_words[0], list_words, NULL) == -1)
			return(-1);
		return(1);
	}
	else
	{
		wait(&status);
		return(1);
	}
}

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(int ac __attribute__((unused)), char **av)
{
	int ret = 0;
	size_t buf_size = 0;
	char **list_words = NULL, *buffer = NULL;
	const char *error = av[0];

	list_words = malloc(BUF_SIZE * sizeof(char *));
	if (list_words == NULL)
	{
		perror(error);
		free(buffer);
		return (1);
	}
	while (1) {
		ret = prompt(buffer, buf_size, list_words);
		if(ret == -1)
			perror(error);
		if (ret != 1)
			break;
	}
	l_free(list_words);
	free(buffer);
	return (ret);
}
