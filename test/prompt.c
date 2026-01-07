#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	size_t buf_size = 32;
	char *buffer = malloc(buf_size * sizeof(char));
	ssize_t res;

	printf("$ ");
	res = getline(&buffer, &buf_size, stdin);
	if (res == -1)
		return(1);
	printf("%s", buffer);
	return (0);
}
