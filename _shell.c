#include "main.h"

/**
* main - creates a simple shell
*
* Return: always 0 success
*/

int main(void)
{
	pid_t pid;
	char cmd[MAX_LEN];
	ssize_t c_read = 0;
	char *f_path;

	while (1)
	{
		write(1, "$ ", 2);
		fflush(stdout);
		c_read = read(STDIN_FILENO, cmd, sizeof(cmd));
		if (c_read == -1)
		{
			perror("Error reading");
			exit(1);
		}
		else if (c_read == 0)
		{
			_putchar('\n');
			break;
		}
		cmd[c_read - 1] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("Error forking");
		}
		else if (pid == 0)
		{
			f_path = _path(cmd);
			_exec(f_path, cmd);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
