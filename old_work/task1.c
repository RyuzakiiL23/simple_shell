#include "main.h"
/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
	write(1, "$ ", 2);
	fflush(stdout);
}

/**
 * execute_command - executes the command using execve
 * @cmd: command to execute
 */
void execute_command(char *cmd)
{
	char *argv[MAX_LEN];

	argv[0] = cmd;
	argv[1] = NULL;
	if (execve(cmd, argv, NULL) == -1)
	{
		perror("Error executing");
		exit(2);
	}
}
