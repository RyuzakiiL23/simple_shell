#include "main.h"

/**
* main - Simple shell
*
* Return: returns 0 success
*/

int main(void)
{
	size_t buffer = 0;
	ssize_t c_read;
	char *exitArg, *exitCmd, *cmd = NULL;
	char *arguments[MAX_LEN];
	int exitStatus = 0;

	while (1)
	{
		write(1, "$ ", 2);
		c_read = getline(&cmd, &buffer, stdin);

		if (c_read == -1)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(1);
		}
		if (strcmp(cmd, "exit\n") == 0)
		{
			free(cmd);
			exit(0);
		}
		else if (c_read == EOF)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(1);
		}
		else
		{
		removeTrailingNewline(cmd);
		tokenizeCommandLine(cmd, arguments);
		performFork(cmd, arguments);

		wait(NULL);
		}
	}
	free(cmd);
	return (0);
}
