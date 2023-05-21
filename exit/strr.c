#include "main.h"

/***************STRLEN*****************/

/**
  * _strlen - returns the length of a string.
  *
  * @s: integer to be printed
  *
  * Return: always i (success)
  *
  */

int _strlen(char *s)
{
	int i = 0;

	for (; *s != '\0'; s++)
	{
		i++;
	}
	return (i);
}

/***************STRCPY*******************/

/**
 * _strcpy - Copy a string
 * @dest: Destination value
 * @src: Source value
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
{
	dest[i] = src[i];
}
	dest[i++] = '\0';
	return (dest);
}

/******************STRCAT*********************/

/**
 *  _strcat - Combines two strings
 *  @dest: destination string
 *  @src: source string
 *  Return: returns a pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j;

	while (dest[i])
	{
		i++;
	}
	for (j = 0; src[j] != 0; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*******************MEMCOPY*******************/

/**
 * _memcpy - Entry point
 *
 * @dest: destination
 *
 * @src: source memory address
 *
 * @n: number of bytes
 *
 * Return: Returns destination
 */


char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
