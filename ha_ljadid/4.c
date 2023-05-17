#include <stdio.h>
#include "main.h"

// Function prototypes
void removeTrailingNewline(char* str);
void tokenizeCommandLine(char* cmd, char** arguments);
void executeCommand(char* executable, char** arguments, char* envp[]);
void performFork(char* cmd, char *arguments[], char* envp[]);

int main(int argc, char* argv[], char* envp[])
{
	char* cmd = NULL;
	size_t buffer = 0;
	ssize_t c_read;

	while (1)
	{
		write(1, "$ ", 2);

		c_read = getline(&cmd, &buffer, stdin);

		if (c_read == -1)
		{
			/*perror("reading");*/
			write (1, "\n",1);
			exit(1);
		}
		if (_strcmp(cmd, "exit") == 0)
		{
			write (1, "\n",1);
			break;
		}

		if (c_read == EOF)
		{
			write (1, "\n",1);
			exit(1);
		}

		removeTrailingNewline(cmd);

		char* arguments[100];
		tokenizeCommandLine(cmd, arguments);

		performFork(cmd,arguments, envp);

		wait(NULL);
	}

	free(cmd);

	return 0;
}

// Function definitions

void removeTrailingNewline(char* str)
{
	int length = strlen(str);
	while (length > 0 && (str[length - 1] == '\n' || str[length - 1] == '\r'))
	{
		str[--length] = '\0';
	}
}

void tokenizeCommandLine(char* cmd, char** arguments)
{
	char* token = strtok(cmd, " "); // Tokenize the command line by space
	char* executable = token;
	int arg_count = 0;

	while (executable != NULL)
	{
		arguments[arg_count++] = executable;
		executable = strtok(NULL, " ");
	}

	arguments[arg_count] = NULL; // Null-terminate the arguments array
}

void executeCommand(char* executable, char** arguments, char* envp[])
{
	if (execve(executable, arguments, envp) == -1)
	{
		perror("Error executing");
		exit(2);
	}
}

void performFork(char* cmd, char *arguments[], char* envp[])
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("Error forking");
	}
	else if (pid == 0)
	{
		char* env_variable = NULL;
		int i = 0;
		while (envp[i] != NULL)
		{
			char* key = strtok(envp[i], "=");
			char* value = strtok(NULL, "=");
			if (strcmp(key, "PATH") == 0)
			{
				env_variable = value;
				break;
			}
			i++;
		}

		if (env_variable == NULL)
		{
			perror("PATH variable not found");
			exit(2);
		}

		char* const path[] = { env_variable, NULL };
		char* dir;
		char* f_path;

		dir = strtok(path[0], ":");
		while (dir != NULL)
		{
			f_path = malloc(strlen(dir) + strlen(cmd) + 2);
			strcpy(f_path, dir);
			strcat(f_path, "/");
			strcat(f_path, cmd);
			if (access(f_path, F_OK) == 0)
			{
				break;
			}
			free(f_path);
		
dir = strtok(NULL, ":");
		}

		if (dir == NULL)
		{
			printf("Executable not found.\n");
			exit(2);
		}

		executeCommand(f_path, arguments, envp);
	}
}

