#include "main.h"

/**
* main - Simple shell
* @argc: number of arguments
* @argv: array of arguments passed
* @envp: a pointer to the environment
* Return: returns 0 success
*/

int main(int argc, char *argv[], char *envp[])
{
	char *cmd = NULL;
	size_t buffer = 0;
	ssize_t c_read;
	char *_exit = "exit\n";
	char *arguments[MAX_LEN];
	(void)argc;
	(void)argv;
	while (1)
	{
		write(1, "$ ", 2);

		c_read = getline(&cmd, &buffer, stdin);

		if (c_read == -1)
		{
			/*perror("reading");*/
			write(1, "\n", 1);
			exit(1);
		}
		if (_strcmp(cmd, _exit) == 0)
		{
			break;
		}

		if (c_read == EOF)
		{
			write(1, "\n", 1);
			exit(1);
		}

		removeTrailingNewline(cmd);

		tokenizeCommandLine(cmd, arguments);

		performFork(cmd, arguments, envp);

		wait(NULL);
	}
	free(cmd);
	return (0);
}
