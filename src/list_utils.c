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
 * If data allocation for new node fails frees all the list data and 
 * returns 1. If new node is added returns 0.
*/
int	add_to_list(list_t *list, int value)
{
	node_t	*new_node = (node_t *)malloc(sizeof(node_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc: data allocation failed\n");
		free_list(list);
		list = NULL;
		return (1);
	}
	new_node->value = value;
	new_node->next = list->head;
	list->head = new_node;
	return (0);
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

/* #include <unistd.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr,"Error: use ./a.out <nbr_of_list_nodes>\n");
		return (EXIT_FAILURE);
	}

	int max_nbr = atoi(argv[1]);

	if (max_nbr <= 0)
	{
		fprintf(stderr, "Error: introduce a positive number\n");
		return (EXIT_FAILURE);
	}
	
	list_t *list = create_list();
	if (!list)
	{
		fprintf(stderr, "Error: malloc: data allocation failed\n");
		return (EXIT_FAILURE);
	}
	for (int i = 1; i <= max_nbr; i++)
	{
		if (add_to_list(list, i))
			return (EXIT_FAILURE);
	}
	print_list(list);
	free_list(list);
	return (EXIT_SUCCESS);
}
 */