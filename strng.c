#include "shell.h"

/**
 * starts_with - to check if nee starts with hay
 * @hay_stack: string to be searched
 * @nee_dle: to be founbd
 * Return: NULL
 */
char *starts_with(const char *hay_stack, const char *nee_dle)
{
	while (*nee_dle)
		if (*nee_dle++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * _strcat - will concatenate string
 * @desti: destination of the buffer
 * @srce: source
 * Return: pointer
 */
char *_strcat(char *desti, char *srce)
{
	char *retn = desti;

	while (*desti)
	{
		desti++;
	}
	while (*srce)
	{
		*desti++ = *srce++;
	}
	*desti = *srce;
	return (retn);
}

/**
 * _strlen - will return string length
 * @sg: the string length that will be checked
 * Return: the int str length
 */
int _strlen(char *sg)
{
	int j = 0;

	if (!sg)
	{
		return (0);
	}
	while (*sg++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @sg2: second string
 * @sg1: the first string
 * Return: - or + or 0
 */
int _strcmp(char *sg1, char *sg2)
{
	while (*sg1 && *sg2)
	{
		if (*sg1 != *sg2)
		{
			return (*sg1 - *sg2);
		}
		sg1++;
		sg2++;
	}
	if (*sg1 == *sg2)
	{
		return (0);
	}
	else
	{
		return (*sg1 < *sg2 ? -1 : 1);
	}
}



