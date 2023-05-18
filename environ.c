#include "shell.h"

/**
 * make_env - make the shell environment from the environment passed to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */

char **make_env(char **env)
{
	char **newenv = NULL;
	size_t j;

	for (j = 0; env[j] != NULL; j++)
		;
	newenv = malloc(sizeof(char *) * (j + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (j = 0; env[j] != NULL; j++)
		newenv[j] = _strdup(env[j]);
	newenv[j] = NULL;
	return (newenv);
}

/**
 * free_env - free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */

void free_env(char **env)
{
	unsigned int j;

	for (j = 0; env[j] != NULL; j++)
		free(env[j]);
	free(env);
}
