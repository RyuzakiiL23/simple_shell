#include "main.h"

/**
 * shell_interactive - Interactive simple shell
 * Return: Returns nothing
 */

void shell_interactive(void)
{
	size_t buffer = 0;
	ssize_t c_read;
	char *_exit = "exit\n", *cmd = NULL;
	char **new_environ;

	while (1)
	{
		prompt();
		c_read = readCommand(&cmd, &buffer);

		if (c_read == (ssize_t)-1)
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

			if (c_read == (ssize_t)EOF)
			{
				write(STDOUT_FILENO, "\n", 1);
				free(cmd);
				exit(EXIT_SUCCESS);
			}
			new_environ = env(environ);
			handleCommand(cmd, new_environ);
		}
	}
}
