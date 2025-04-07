#ifndef LIST_UTILS_H
# define LIST_UTILS_H

# include <stdio.h>
# include <stdlib.h>

typedef struct node_s
{
	int value;
	struct node *next;
}	node_t;

typedef struct list_s
{
	node_t *head;
}	list_t;

list_t	*create_list();
void	free_list(list_t *list);
void	add_to_list(list_t *list, int value);
void	print_list(list_t *list);

#endif
