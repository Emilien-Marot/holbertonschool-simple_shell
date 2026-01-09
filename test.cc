#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_to_list(char *string, char **list)
{
	int i = 0;

	if (list == NULL || string == NULL)
		return (-1);
	printf("%p\n", strtok(string, " "));
	while (list[i] != NULL)
	{
		printf("%s\n", list[i]);
		i++;
		list[i] = strtok(NULL, "\t\n ");
	}
	return (0);
}

void test(char *str_init)
{
    char **list = NULL, *str = NULL;
    int i;

    
    list = malloc(10 * sizeof(char *));
    i = string_to_list(str,list);
    printf("%d\n", i);
    for(i = 0; list[i] != NULL; i++)
    {
        printf("list[%d] = \"%s\"\n", i, list[i]);
    }
}

int main()
{
	char *s1 = strdup("Hello World");
    test(s1);
    /*test("   ");
    test("  Hello\t World\n!   \t\n");*/
    return 0;
}
