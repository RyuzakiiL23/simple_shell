#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LEN 100

void _putchar(char c);
/****************TASK1_PROTOTYPES******************/

void execute_command(char *cmd);
char *_path(char *cmd);
void _exec(char *f_path, char *cmd);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);


#endif
