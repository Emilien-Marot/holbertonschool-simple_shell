#include <stdio.h>
#include <stdlib.h>
#include<string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int i, j, same;

	for(i = 0; environ[i] != NULL; i++)
	{
		same = 1;
		for(j = 0; name[j] != '\0'; j++)
		{
			if(environ[i][j] != name[j])
			{
				same = 0;
				break;
			}
		}
		if(same && environ[i][j] == '=' && name[j] == '\0')
		{
			return(&(environ[i][j+1]));
		}
	}
	return(NULL);
}


