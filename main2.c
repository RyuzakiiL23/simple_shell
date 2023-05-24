#include "main.h"

/**
* shell_non_interactive - non interactive simple shell
* Return: returns nothing
*/

void shell_non_interactive(void)
{
	size_t buffer = 0;
	ssize_t c_read;
	char *_exit = "exit\n", *cmd = NULL;
	char *arguments[MAX_LEN], **new_environ;

		fflush(stdout);
		c_read = getline(&cmd, &buffer, stdin);
		if (c_read == -1)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
		while (*cmd == ' ')
		{
			cmd++;
		}
		if (_strcmp(cmd, _exit) == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (c_read == EOF)
		{
			write(1, "\n", 1);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
		new_environ = env(environ);
		removeTrailingNewline(cmd);
		tokenizeCommandLine(cmd, arguments);
		performFork(cmd, arguments, new_environ);
		wait(NULL);
		}
		}
		free(cmd);
}
