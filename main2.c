#include "main.h"

/**
* shell_non_interactive - non interactive simple shell
* Return: returns nothing
*/

void shell_non_interactive(void)
{
	size_t buffer = 0;
	ssize_t c_read;
	char *_exit = "exit\n", *cmd = NULL, *trimmed_cmd;
	char *arguments[MAX_LEN], **new_environ;

	c_read = getline(&cmd, &buffer, stdin);
	if (c_read == -1)
	{
		write(1, "\n", 1);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else
		{
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

		trimmed_cmd = cmd;
		while (*trimmed_cmd == ' ')
		{
			trimmed_cmd++;
		}
		new_environ = env(environ);
		removeTrailingNewline(trimmed_cmd);
		tokenizeCommandLine(trimmed_cmd, arguments);
		performFork(trimmed_cmd, arguments, new_environ);
		wait(NULL);
	}
}
