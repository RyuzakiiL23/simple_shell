#include "main.h"

/**
 * execute_command - executes the command using execve
 * @cmd: command to execute
 */
void execute_command(char *cmd)
{
	char *argv[MAX_LEN];
	char *token = strtok(cmd, " ");
	int len = 0;

		while (token != NULL)
		{
				argv[len] = token;
				token = strtok(NULL, " ");
				len++;
		}

	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error executing");
		exit(2);
	}
}
