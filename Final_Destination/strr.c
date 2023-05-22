#include "main.h"
#include <stdbool.h>

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
 * _strspn - Gets the length of the initial segment of a string that consists
 *           only of characters from a specified accept string.
 * @str: The string to be searched
 * @accept: The characters to search for
 *
 * Return: The length of the initial segment of 'str' that consists only of
 *         characters from 'accept'.
 */

size_t _strspn(const char *str, const char *accept)
{
	size_t length = 0;

	while (*str && _strchr(accept, *str++))
		length++;

	return (length);
}

/**
 * _strcspn - Gets the length of the initial segment of a string that consists
 *            of characters not in a specified reject string.
 * @str: The string to be searched
 * @reject: The characters to exclude
 *
 * Return: The length of the initial segment of 'str' that consists only of
 *         characters not in 'reject'.
 */

size_t _strcspn(const char *str, const char *reject)
{
	size_t length = 0;
	bool found;
	const char *reject_ptr;

	while (*str)
	{
		found = false;

		for (reject_ptr = reject; *reject_ptr; reject_ptr++)
		{
			if (*str == *reject_ptr)
			{
				found = true;
				break;
			}
		}

		if (found)
			break;

		length++;
		str++;
		}

	return (length);
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
	char *token_end;

	if (str == NULL)
		str = next_token;

	str += _strspn(str, delim);

	if (*str == '\0')
		return (NULL);

	token_end = str + _strcspn(str, delim);

	if (*token_end != '\0')
		*token_end++ = '\0';

	next_token = token_end;

	return (str);
}
