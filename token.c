#include "shell.h"

/**
 * **strtow - will split thue string into two
 * @strg: input
 * @e: delimiter
 * Return: pointer o/w null
 */

char **strtow(char *strg, char *e)
{
	int j, k, l, n, num_words = 0;
	char **t;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (j = 0; strg[j] != '\0'; j++)
		if (!is_delim(strg[j], e) && (is_delim(strg[j + 1], e) || !strg[j + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	t = malloc((1 + num_words) * sizeof(char *));
	if (!t)
	{
		return (NULL);
	}
	for (j = 0, k = 0; k < num_words; k++)
	{
		while (is_delim(strg[j], e))
			j++;
		l = 0;
		while (!is_delim(strg[j + l], e) && strg[j + l])
			l++;
		t[k] = malloc((l + 1) * sizeof(char));
		if (!t[k])
		{
			for (l = 0; l < k; l++)
				free(t[l]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			t[k][n] = strg[j++];
		t[k][n] = 0;
	}
	t[k] = NULL;
	return (t);
}

/**
 * **strtow2 - will split the string
 * @strg: string
 * @e: delimiter
 * Return: pointer
 */
char **strtow2(char *strg, char e)
{
	int j, k, l, n, num_words = 0;
	char **t;

	if (strg == NULL || strg[0] == 0)
	{
		return (NULL);
	}
	for (j = 0; strg[j] != '\0'; j++)
		if ((strg[j] != e && strg[j + 1] == e) ||
		    (strg[j] != e && !strg[j + 1]) || strg[j + 1] == e)
			num_words++;
	if (num_words == 0)
		return (NULL);
	t = malloc((1 + num_words) * sizeof(char *));
	if (!t)
		return (NULL);
	for (j = 0, k = 0; k < num_words; k++)
	{
		while (strg[j] == e && strg[j] != e)
			j++;
		l = 0;
		while (strg[j + l] != e && strg[j + l] && strg[j + l] != e)
			l++;
		t[k] = malloc((k + 1) * sizeof(char));
		if (!t[k])
		{
			for (l = 0; l < k; l++)
				free(t[l]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			t[k][n] = strg[j++];
		t[k][n] = 0;
	}
	t[k] = NULL;
	return (t);
}
