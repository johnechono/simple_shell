#include "shell.h"

/**
 * check_match - checks if character matches a string
 * @c: character string
 * @str: string that will be checked
 * Return: 1 if positive
 * O/W: 0
 */

unsigned int check_match(char c, const char *str)
{
	unsigned int j;

	while (str[j] != '\0')
	{
		if (c == str[j])
		return (1);
		j++;
	}
	return (0);
}

/**
 * new_strtok - custom version
 * @delim: it's characters we mark off string in parts
 * @str: string
 * Return: nothing
 */
char *new_strtok(char *str, const char *delim)
{
	unsigned int j;
	static char *nxt_tok;
	static char *tok_strt;

	if (str != NULL)
		nxt_tok = str;
	tok_strt = nxt_tok;
	if (tok_strt == NULL)
		return (NULL);
	for (j = 0; nxt_tok[j] != '\0'; j++)
	{
		if (check_match(nxt_tok[j], delim) == 0)
			break;
	}
	if (nxt_tok[j] == '\0' || nxt_tok[j] == '#')
	{
		nxt_tok = NULL;
		return (NULL);
	}
	tok_strt = nxt_tok + j;
	nxt_tok = tok_strt;
	for (j = 0; nxt_tok[j] != '\0'; j++)
	{
		if (check_match(nxt_tok[j], delim) == 1)
			break;
	}
	if (nxt_tok[j] == '\0')
		nxt_tok = NULL;
	else
	{
		nxt_tok[j] = '\0';
		nxt_tok = nxt_tok + j + 1;
		if (*nxt_tok == '\0')
			nxt_tok = NULL;
	}
	return (tok_strt);

}
