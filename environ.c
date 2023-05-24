#include "shell.h"

/**
 * free_env - freeing the environ
 * @env: shell environ
 * Return: void
 */

void free_env(char **env)
{
	unsigned int j;

	j = 0;
	while (env[j] != NULL)
		free(env[j]);
	j++;
	free(env);
}

/**
 * make_env - making the environ
 * @env: the environ
 * Return: pointer
 */

char **make_env(char **env)
{
	size_t j;
	char **new_env = NULL;

	for (j = 0; env[j] != NULL; j++)
		;
	new_env = malloc(sizeof(char *) * (j + 1));
	if (new_env == NULL)
	{
		perror("Failure");
		exit(1);
	}
	for (j = 0; env[j] != NULL; j++)
		new_env[j] = _strdup(env[j]);
	new_env[j] = NULL;
	return (new_env);
}
