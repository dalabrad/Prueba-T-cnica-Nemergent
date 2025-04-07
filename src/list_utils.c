#include "list_utils.h"

/*
 * This function allocates data for a new list, and points the head of list to NULL.
*/
list_t	*create_list(void)
{
	list_t	*list = (list_t *)malloc(sizeof(list_t));

	if (!list)
	return (NULL);
	list->head = NULL;
	return (list);
}

/*
 * This function frees all the data allocated for the list.
*/
void    free_list(list_t *list) 
{
	if (!list)
		return ;
	
	node_t *current = list->head;

	while (current)
	{
		node_t *next = current->next;

		free(current);
		current = next;
    }
    free(list);
}

/*
 * This function adds a new node with value on top of the list.
 * 		~ TO DO: maybe a return int or bool and free list when 
 * 				 data allocation fails.
*/
void	add_to_list(list_t *list, int value)
{
	node_t	*new_node = (node_t *)malloc(sizeof(node_t));

	if (!new_node)
		return ;
	new_node->value = value;
	new_node->next = list->head;
	list->head = new_node;
}

/*
 * This function prints the list in the format:
 * 		value_1->value_2->...->last_value
*/
void	print_list(list_t *list)
{
	if (!list)
		return ;

	node_t	*current = list->head;

	while (current)
	{
		printf("%d", current->value);
		if (current->next)
			printf("->");
		current = current->next;
	}
	printf("\n");
}
