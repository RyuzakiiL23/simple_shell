#include "main.h"

/**
 * main - Simple shell
 * Return: returns 0 success
 */

int main(void)
{
    size_t buffer = 0;
    ssize_t c_read;
    char *_exit = "exit\n", *cmd = NULL;
    char *arguments[MAX_LEN], **new_environ;

    while (1)
    {
        write(1, "$ ", 2);
        fflush(stdout);
        c_read = getline(&cmd, &buffer, stdin);
        if (c_read == -1)
        {
            write(1, "\n", 1);
            free(cmd);
            exit(1);
        }
        if (_strcmp(cmd, _exit) == 0)
        {
            free(cmd);
            exit(0);
        }
        if (c_read == EOF)
        {
            write(1, "\n", 1);
            free(cmd);
            exit(1);
        }
        else if (c_read == EOF)
        {
            write(1, "\n", 1);
            free(cmd);
            exit(1);
        }
        else
        {
            removeTrailingNewline(cmd);
            char *token = _strtok(cmd, ";");
            while (token != NULL)
            {
                new_environ = env(environ);
                removeTrailingNewline(token);
                tokenizeCommandLine(token, arguments);
                performFork(token, arguments, new_environ);
                wait(NULL);
                token = _strtok(NULL, ";");
            }
        }
    }
    free(cmd);
    return (0);
}
