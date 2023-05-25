#include "main.h"

/**
* shell_interactive - non interactive simple shell
* Return: returns nothing
*/

void shell_interactive(void)
{
	size_t buffer = 0, c_read;
	char *_exit = "exit\n", *cmd = NULL, *trimmed_cmd;
	char *arguments[MAX_LEN], **new_environ;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
		c_read = getline(&cmd, &buffer, stdin);
		if (*cmd == '\n')
		{
			continue;
		}
		if (c_read == (unsigned long int)-1)
		{
			write(STDOUT_FILENO, "\n", 1);
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
			if (c_read == (unsigned long int)EOF)
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
			if(*trimmed_cmd == '\n')
				{
				continue;
				}
			new_environ = env(environ);
			removeTrailingNewline(trimmed_cmd);
			tokenizeCommandLine(trimmed_cmd, arguments);
			performFork(trimmed_cmd, arguments, new_environ);
			wait(NULL);
		}
	}
}
