#include "main.h"

/*extern char **environ;*/

/* Function prototypes */
void removeTrailingNewline(char *str);
void tokenizeCommandLine(char *cmd, char **arguments);
void executeCommand(char *executable, char **arguments);
void performFork(char *cmd, char *arguments[], char **new_environ);
char **env(char **environ);

/* Function definitions */

/**
 * env - Duplicate the environment variables
 * @environ: The original environment variables
 *
 * Return: The duplicated environment variables
 */

char **env(char **environ)
{
	int environ_count = 0, i, length;
	char **new_environ;

	while (environ[environ_count] != NULL)
	{
		environ_count++;
	}

	new_environ = malloc((environ_count + 1) * sizeof(char *));

	for (i = 0; i < environ_count; i++)
	{
		length = _strlen(environ[i]) + 1;
		new_environ[i] = malloc(length * sizeof(char));
		_strcpy(new_environ[i], environ[i]);
	}

	new_environ[environ_count] = NULL;
	return (new_environ);
}

/**
 * freeEnviron - Free the duplicated environment variables
 * @environ: The duplicated environment variables
 */

void freeEnviron(char **environ)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

/* Other function definitions */
/**
* removeTrailingNewline - removes new lines
* @str: string to be modified
* Return: returns a pointer to the modified string
*/

void removeTrailingNewline(char *str)
{
	int length = _strlen(str);

	while (length > 0 && (str[length - 1] == '\n'))/* || str[length - 1] == '\r'))*/
	{
		str[--length] = '\0';
	}
}

/**
* tokenizeCommandLine - splits the string
* @cmd: the command to be executed
* @arguments: the arguments of our cmd
*/

void tokenizeCommandLine(char *cmd, char **arguments)
{
	char *token, *exitArg;
	int arg_count = 0, exitStatus = 0;
	char *f_cmd = _strtok(cmd, ";");
	size_t len;

	while (f_cmd != NULL)
	{
		len = _strlen(f_cmd);

		while (len > 0 && f_cmd[len - 1] == ' ')
		{
			f_cmd[--len] = '\0';
		}

		if (_strchr(f_cmd, '/') == NULL)
		{
			token = _strtok(f_cmd, " ");
			f_cmd[_strcspn(f_cmd, "\n")] = '\0';

			while (token != NULL)
			{
				if (_strcmp(token, "exit") == 0)
				{
					exitArg = _strtok(NULL, " ");
					if (exitArg != NULL)
					{
						exitStatus = _atoi(exitArg);
					}
					free(f_cmd);
					exit(exitStatus);
				}
				else
				{
					arguments[arg_count++] = token;
					token = _strtok(NULL, " ");
				}
			}
			arguments[arg_count] = NULL;
			f_cmd = _strtok(NULL, ";");
		}
		else
		{
			token = _strtok(f_cmd, " ");
			f_cmd[_strcspn(f_cmd, "\n")] = '\0';

			while (token != NULL)
			{
				arguments[arg_count++] = token;
				token = _strtok(NULL, " ");
			}
			arguments[arg_count] = NULL;
			f_cmd = _strtok(NULL, ";");
		}
	}
}


/**
* executeCommand - executes the command entered
* @executable: the command to be executed
* @arguments: the arguments passed to our executable
*/

void executeCommand(char *executable, char **arguments)
{
	if (execve(executable, arguments, environ) == -1)
	{
		perror("");
		exit(2);
	}
}

/**
* performFork - forks to get two processes
* @cmd: our command
* @arguments: the arguments passed
* @new_environ: the environment
*/

void performFork(char *cmd, char *arguments[], char **new_environ)
{
	char *path[MAX_LEN];
	char *dir, *key, *value;
	char *f_path, *env_variable = NULL;
	int x = 0, i = 0;
	pid_t pid;

	while (new_environ[i] != NULL)
	{
		key = _strtok(new_environ[i], "=");
		value = _strtok(NULL, "=");
		if (_strcmp(key, "PATH") == 0)
		{
			env_variable = value;
			break;
		}
		i++;
	}

	if (env_variable == NULL)
	{
		perror("");
		exit(3);
	}
	else
	{
		path[0] = env_variable;
		path[1] = NULL;
	}

	dir = _strtok(path[0], ":");
	while (dir != NULL)
	{
		f_path = malloc(_strlen(dir) + _strlen(cmd) * 2 + 2);
		if (cmd[x] == '/')
		{
			_strcpy(f_path, cmd);
		}
		else
		{
			_strcpy(f_path, dir);
			_strcat(f_path, "/");
			_strcat(f_path, cmd);
		}
		if (access(f_path, F_OK) == 0)
		{
			break;
		}
		free(f_path);
		dir = _strtok(NULL, ":");
	}
	if (dir == NULL)
	{
		perror("");
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			/*perror("");*/
			exit(3);
		}
		else if (pid == 0)
		{
			executeCommand(f_path, arguments);
		}
		else
		{
			wait(NULL);
		}
	}
	if (dir != NULL)
	{
		free(f_path);
	}
	freeEnviron(new_environ);
}
