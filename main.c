#include "main.h"

/**
* shell_interactive - interactive simple shell
* Return: nthing
*/

void shell_interactive(void)
{
	size_t buffer = 0;
	ssize_t c_read;
	char *_exit = "exit\n", *cmd = NULL;
	char *arguments[MAX_LEN], **new_environ;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
		c_read = getline(&cmd, &buffer, stdin);
		while (*cmd == ' ')
		{
			cmd++;
		}
		if (c_read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		if (_strcmp(cmd, _exit) == 0)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		if (c_read == EOF)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		new_environ = env(environ);
		removeTrailingNewline(cmd);
		tokenizeCommandLine(cmd, arguments);
		performFork(cmd, arguments, new_environ);
	}
	free(cmd);
}
