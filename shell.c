#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void l_free(char **list_w)
{
	int i;

	for(i = 0; list_w[i] != NULL; i++)
	{
		free(list_w[i]);
		list_w[i] = NULL;
	}
}

void print_list(char **list_w)
{
	int i;

	for(i = 0; list_w[i] != NULL; i++)
	{
		printf("%s\n", list_w[i]);
	}
}

void execute(char **list_w)
{
	if (execve(list_w[0], list_w, NULL) == -1)
	{
		perror("Error:");
		exit(1);
	}
}

int main()
{
	size_t buf_size = 1024;
	char **list_w;
	char *buffer, *buf_w;
	ssize_t res;
	int i, j, idx_w = 0;

	buffer = malloc(buf_size * sizeof(char));
	if(buffer == NULL)
		return(1);
	buf_w = malloc(buf_size * sizeof(char));
	if(buf_w == NULL)
	{
		free(buffer);
		return(1);
	}
	list_w = malloc(buf_size * sizeof(char *));
	if(list_w == NULL)
	{
		free(buf_w);
		free(buffer);
		return(1);
	}
	printf("$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
		return(1);
	while(strcmp(buffer, "exit\n") != 0)
	{
		j = 0;
		idx_w = 0;
		buf_w[0] = '\0';
		for(i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == ' ' || buffer[i] == '\n')
			{
				list_w[idx_w] = strdup(buf_w);
				if(list_w == NULL)
				{
					l_free(list_w);
					free(list_w);
					free(buf_w);
					free(buffer);
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
		execute(list_w);
		l_free(list_w);
		printf("$ ");
                res = getline(&buffer, &buf_size, stdin);
                if (res == -1)
                        return(1);
	}
	free(buf_w);
	free(buffer);
	free(list_w);
	return(0);
}
