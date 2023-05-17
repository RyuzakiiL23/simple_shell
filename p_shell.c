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
	char *argv[MAX_LEN];
	ssize_t c_read = 0;
	char *const path[] = { getenv("PATH"), NULL };
	char *dir, *f_path;

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
		_path(cmd);
		/*dir = strtok(path[0], ":");
		while (dir != NULL)
		{
			//f_path = _strcat(dir, cmd);
			f_path = malloc(_strlen(dir) + _strlen(cmd) + 2);
			sprintf(f_path, "%s/%s", dir, cmd);
			if (access(f_path, F_OK) == 0)
			{
				break;
			}
			free(f_path);
			dir = strtok(NULL, ":");
		}
		if (dir == NULL)
		{
			perror("err");
			continue;
		}*/
		pid = fork();
		if (pid == -1)
		{
			perror("Error forking");
		}
		else if (pid == 0)
		{
		_exec(f_path);
			/*argv[0] = f_path;
			argv[1] = NULL;
			if (execve(f_path, argv, NULL) == -1)
			{
				perror("Error executing");
				exit(2);
			}*/
		}
		wait(NULL);
	}
	return (0);
}
