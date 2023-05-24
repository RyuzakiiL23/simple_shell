#include "main.h"
char *_path(char *cmd)
{
	char *const path[] = {getenv("PATH"), NULL};
	char *dir, *f_path;

	dir = strtok(path[0], ":");
		while (dir != NULL)
		{
			f_path = malloc(_strlen(dir) + _strlen(cmd) + 2);
			sprintf(f_path, "%s/%s", dir, cmd);
			if (access(f_path, F_OK) == 0)
			{
				break;
			}
			free(f_path);
			dir = strtok(NULL, ":");
		}
		/*if (dir == NULL)
		{
			perror("err");
			continue;
		}*/
	return(f_path);
}

void _exec(char *f_path, char *cmd)
{
	char *argv[MAX_LEN];

	cmd = NULL;
	argv[0] = NULL;
	argv[1] = cmd;
	argv[2] = NULL;
	if (execve(f_path, argv, NULL) == -1)
	{
		perror("Error executing");
		exit(2);
	}
}
