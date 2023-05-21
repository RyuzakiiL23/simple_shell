#include "main.h"


/**
  * _strcmp - Compares two strings
  * @s1: The first string
  * @s2: The second string
  *
  * Return: int value
  */

int _strcmp(char *s1, char *s2)
{
	int len_s = 0;
	int len_s2 = 0;
	int len = 0;
	int result = 0;
	int cpr;

	while (s1[len_s])
	{
		len_s++;
	}
	while (s2[len_s2])
	{
		len_s2++;
	}

	if (len_s <= len_s2)
	{
		cpr = len_s;
	}
	else
	{
		cpr = len_s2;
	}
	while (len <= cpr)
	{
		if (s1[len] == s2[len])
		{
			len++;
			continue;
		}
		else
		{
			result = s1[len] - s2[len];
			break;
		}
		len++;
	}
	return (result);
}

/**
* _strchr - Entry Point
*
* @s: string to look in
* @c: character to look for
*
* Return: returns s+i or NULL
*/

const char *_strchr(const char *s, char c)
{
	unsigned int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (s + i);
		}
		i++;
	}
	return (NULL);
}

/**
* _strtok - tokenizes a string
*
* @str: the string to be tokenized
* @delim: the delimeter or separator
* Return: returns the splitted string
*/

char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	int i = 0;
	char *token;

	if (str != NULL)
	{
		next_token = str;
	}
	if (next_token == NULL || *next_token == '\0')
	{
		return (NULL);
	}
	token = (char *)malloc(sizeof(char) * MAX_LEN);
	if (token == NULL)
	{
		return (NULL);
	}
	while (*next_token != '\0' && _strchr(delim, *next_token) != NULL)
	{
		next_token++;
	}
	while (*next_token != '\0' && _strchr(delim, *next_token) == NULL)
	{
		token[i] = *next_token;
		next_token++;
		i++;
	}
	token[i] = '\0';
	if (*next_token == '\0')
	{
		next_token = NULL;
	}
	return (token);
}
