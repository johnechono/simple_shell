#include "shell.h"

/**
 * free_list - will frees all nodes in the list
 * @head_pntr: pointer address
 * Return: null
 */
void free_list(list_t **head_pntr)
{
	list_t *node, *node_next, *head;

	if (!head_pntr || !*head_pntr)
	{
		return;
	}
	head = *head_pntr;
	node = head;
	while (node)
	{
		node_next = node->next;
		free(node->str);
		free(node);
		node = node_next;
	}
	*head_pntr = NULL;
}

/**
 * add_node - will adds the node
 * @head: pointer address
 * @num: history by node index
 * @str: string
 * Return: size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *head_new;

	if (!head)
	{
		return (NULL);
	}
	head_new = malloc(sizeof(list_t));
	if (!head_new)
	{
		return (NULL);
	}
	_memset((void *)head_new, 0, sizeof(list_t));
	head_new->num = num;
	if (str)
	{
		head_new->str = _strdup(str);
		if (!head_new->str)
		{
			free(head_new);
			return (NULL);
		}
	}
	head_new->next = *head;
	*head = head_new;
	return (head_new);
}

/**
 * add_node_end - will add a node to the list
 * @head: head pointer address
 * @num: history of node index
 * @str: node string
 * Return: size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node_new, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	node_new = malloc(sizeof(list_t));
	if (!node_new)
		return (NULL);
	_memset((void *)node_new, 0, sizeof(list_t));
	node_new->num = num;
	if (str)
	{
		node_new->str = _strdup(str);
		if (!node_new->str)
		{
			free(node_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = node_new;
	}
	else
		*head = node_new;
	return (node_new);
}

/**
 * print_list_str - will print only the string
 * @p: first node pointer
 * Return: size
 */
size_t print_list_str(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_puts(p->str ? p->str : "(null)");
		_puts("\n");
		p = p->next;
		j++;
	}

	return (j);
}

/**
 * delete_node_at_index - will delete the given index node
 * @in_dex: deletable node index
 * @head: pointer address
 * Return: 1 O/W 0
 */
int delete_node_at_index(list_t **head, unsigned int in_dex)
{
	list_t *node, *node_prev;
	unsigned int j = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!in_dex)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == in_dex)
		{
			node_prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		node_prev = node;
		node = node->next;
	}
	return (0);
}
