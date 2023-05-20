#include "shell.h"

/**
 * tokenize - delim tokenizer
 * @delimiter: delimiter
 * @buffer: buffer
 * Return: pointer
 */
char **tokenize(char *buffer, char *delimiter)
{
	size_t j = 0, m_count = 10;
	char **token = NULL;

	token = malloc(sizeof(char *) * m_count);
	if (token == NULL)
	{
		perror("Error");
		return (NULL);
	}
	if (buffer == NULL)
	{
		return (NULL);
	}
	for (j = 0; (token[j] = new_strtok(buffer, delimiter)) != NULL; j++)
	{
		if (j == m_count)
		{
			token = _realloc(token, &m_count);
			if (token == NULL)
			{
				perror("Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (token);
}
