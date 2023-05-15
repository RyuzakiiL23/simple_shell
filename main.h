#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LEN 100
#define BUFSIZE 1024

void _putchar(char c);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strcmp(char *s1, char *s2);

char *trim(char *command);
void *fxw(char *trimmed_command);

#endif
