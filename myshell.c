#include <stdio.h>
#include <string.h>

void parsestr(char *cmd)
{
	char *token = strtok(cmd," \t\n");
	while (token != NULL)
	{
		
		printf ("%s\n",token);
		token = strtok(NULL, " \t\n");
	}

}
