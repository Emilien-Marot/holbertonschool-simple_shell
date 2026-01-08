#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUF_SIZE 1024

void l_free(char **list_w)
{
	int i;

	for (i = 0; list_w[i] != NULL; i++)
	{
		free(list_w[i]);
		list_w[i] = NULL;
	}
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

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status, i = 0, ret = 0;
	size_t buf_size = BUF_SIZE;
	char **list_w, *buffer;
	ssize_t res;

	buffer = malloc(BUF_SIZE * sizeof(char));
	if (buffer == NULL)
	{
		perror("Error: could not allocate memory to the buffer");
		return (1);
	}
	list_w = malloc(BUF_SIZE * sizeof(char *));
	if (list_w == NULL)
	{
		perror("Error: could not allocate memory to the buffer");
		free(buffer);
		return (1);
	}
	do {
		i++;
		printf("$ ");
		res = getline(&buffer, &buf_size, stdin);
		if (res == -1)
		{
			if (errno != 0)
				perror("Error_1");
			else
				printf("\n");
			break;
		}
		if (string_to_list(buffer, list_w) == 1)
		{
			perror("Error_2");
			ret = 1;
			break;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error_3");
			ret = 1;
			break;
		}
		if (child_pid == 0)
		{
			if (execve(list_w[0], list_w, NULL) == -1)
				perror("Error_4");
		}
		else
			wait(&status);
	} while (child_pid != 0);
	l_free(list_w);
	free(list_w);
	free(buffer);
	return (0);
}

