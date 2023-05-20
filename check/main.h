#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LEN 1024

/*--------mainF-------*/
void removeTrailingNewline(char *str);
void tokenizeCommandLine(char *cmd, char **arguments);
void executeCommand(char *executable, char **arguments);
void performFork(char *cmd, char *arguments[]);


/*-------staticLib--------*/
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
void _putchar(char c);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
const char *_strchr(const char *s, char c);
char *_strtok(char *str, const char *delim);
ssize_t *_getline(char **lineptr, size_t *n, FILE *filename);

#endif
