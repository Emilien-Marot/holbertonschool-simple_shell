#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>

void l_free(char **list_w)
{
	int i;

	for(i = 0; list_w[i] != NULL; i++)
	{
		free(list_w[i]);
		list_w[i] = NULL;
	}
}

int string_to_list(char *string, char **list, size_t buf_size)
{
	int i, j = 0, idx_w = 0;
	char *word;

	word = malloc(buf_size * sizeof(char));
	if(word == NULL)
		return(1);
	j = 0;
	idx_w = 0;
	word[0] = '\0';
	for(i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == ' ' || string[i] == '\n')
		{
			list[idx_w] = strdup(word);
			if(list == NULL)
			{
				l_free(list);
				return(1);
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
	return(0);
}

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	size_t buf_size = 1024;
	int status, i = 0;
	char **list_w;
	char *buffer;
	ssize_t res;

	do
	{
		i++;
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			buffer = malloc(buf_size * sizeof(char));
			if(buffer == NULL)
				return(1);
			list_w = malloc(buf_size * sizeof(char *));
			if(list_w == NULL)
			{
				free(buffer);
				return(1);
			}
			printf("$ ");
			res = getline(&buffer, &buf_size, stdin);
			if (res == -1)
			{
				free(buffer);
				free(list_w);
				return(1);
			}
			if(string_to_list(buffer, list_w, buf_size) == 1)
			{
				free(buffer);
                                free(list_w);
                                return(1);
			}
			if (execve(list_w[0], list_w, NULL) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(&status);
		}
	}
	while (child_pid != 0);
	return (0);
}
