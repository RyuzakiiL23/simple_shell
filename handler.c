#include "main.h"

/**
 * prompt - Display the shell prompt
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}

/**
 * readCommand - Read the user input command
 * @cmd: Pointer to the command string
 * @buffer: Pointer to the buffer size for getline
 * Return: Number of characters read
 */
ssize_t readCommand(char **cmd, size_t *buffer)
{
	ssize_t c_read;

	c_read = getline(cmd, buffer, stdin);
	return (c_read);
}

/**
 * handleCommand - Process the user input command
 * @cmd: Command string
 * @new_environ: Duplicated environment variables
 */
void handleCommand(char *cmd, char **new_environ)
{
	char *trimmed_cmd;
	char *arguments[MAX_LEN];

	trimmed_cmd = cmd;
	while (*trimmed_cmd == ' ')
		trimmed_cmd++;

	if (*trimmed_cmd == '\n')
		return;

	removeTrailingNewline(trimmed_cmd);
	tokenizeCommandLine(trimmed_cmd, arguments);
	performFork(trimmed_cmd, arguments, new_environ);
	wait(NULL);
}
