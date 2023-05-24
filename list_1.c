#include "shell.h"

/**
 * node_starts_with - Returns node whose str starts with prefix
 * @node: pointer to list
 * @prefix: string
 * @c: next character after prefix
 * Return: null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index
 * @head: pointer to list head
 * @node:  pointer to the node
 * Return: index of node
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}

/**
 * list_len - Gets the length
 * @h: pointer
 * Return: size
 */
size_t list_len(const list_t *h)
{
	size_t _j = 0;

	while (h)
	{
		h = h->next;
		_j++;
	}
	return (_j);
}

/**
 * list_to_strings - an array of strings
 * @head: pointer to first node
 * Return: array of str
 */
char **list_to_strings(list_t *head)
{
	size_t j = list_len(head), k;
	list_t *node = head;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of the list_t
 * @h: pointer
 * Return: size
 */
size_t print_list(const list_t *h)
{
	size_t _j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		_j++;
	}
	return (_j);
}

