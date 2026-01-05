#include <stdio.h>
#include <unistd.h>
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

void string_to_list(char *string, char **list)
{
	int i, j = 0, idx_w = 0;
	char *buf_w;

	buf_w = malloc(buf_size * sizeof(char));
	if(buf_w == NULL)
		return(1);
	j = 0;
	idx_w = 0;
	buf_w[0] = '\0';
	for(i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == ' ' || string[i] == '\n')
		{
			list_w[idx_w] = strdup(buf_w);
			if(list_w == NULL)
			{
				l_free(list_w);
				return(1);
			}
			idx_w++;
			list_w[idx_w] = NULL;
			j = 0;
		}
		else
		{
			buf_w[j] = buffer[i];
			j++;
		}
		buf_w[j] = '\0';
	}
}

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status, i = 0;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

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
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(&status);
		}
	}
	while (i < 5 && child_pid != 0);
	return (0);
}
