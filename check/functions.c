#include "main.h"

extern char **environ;
/*--------------- Function prototypes -----------------*/
void removeTrailingNewline(char  *str);
void tokenizeCommandLine(char *cmd, char **arguments);
void executeCommand(char *executable, char **arguments);
void performFork(char *cmd, char *arguments[]);


/*--------------- Function definitions-----------------*/

/**
* removeTrailingNewline - removes new lines
* @str: string to be modified
* Return: returns a pointer to the modified string
*/

void removeTrailingNewline(char *str)
{
	int length = _strlen(str);

	while (length > 0 && (str[length - 1] == '\n' || str[length - 1] == '\r'))
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
	char *token = _strtok(cmd, " ");
	char *executable = token;
	int arg_count = 0;

	while (executable != NULL)
	{
		arguments[arg_count++] = executable;
		executable = _strtok(NULL, " ");
	}

	arguments[arg_count] = NULL;
}

/**
* executeCommand - executes the command entered
* @executable: the command to be executed
* @arguments: the arguments passed to our executable
* @envp: the environment
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
* @envp: the environment
*/

void performFork(char *cmd, char *arguments[])
{
	char *path[MAX_LEN];
	char *dir, *key, *value, *f_path;
	int x = 0, i = 0;
	pid_t pid;
	char *env_variable = NULL;

	while (environ[i] != NULL)
	{
		key = _strtok(environ[i], "=");
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
	path[0] = env_variable;
	path[1] = NULL;

	dir = _strtok(path[0], ":");
	while (dir != NULL)
	{
		f_path = malloc(_strlen(dir) + _strlen(cmd) + 2);
		if (cmd[x] == '/')
		{
			f_path = cmd;
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
		perror("");
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
}
