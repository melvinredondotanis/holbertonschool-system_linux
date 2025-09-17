#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/**
 * struct node_s - Node structure
 *
 * @content: Custom content
 * @prev:    Pointer to the previous node in the list
 * @next:    Pointer to the next node in the list
 */
typedef struct node_s
{
	void *content;
	struct node_s *prev;
	struct node_s *next;
} node_t;

/**
 * struct list_s - List structure
 *
 * @head: Ponter to the front node
 * @tail: Ponter to the back node
 * @size: Number of nodes in the list
 */
typedef struct list_s
{
	node_t *head;
	node_t *tail;
	size_t size;
} list_t;

typedef void (*node_func_t)(void *);

/* list.c */
node_t *node_create(void *content);
node_t *list_add(list_t *list, void *content);
list_t *list_init(list_t *list);
void list_destroy(list_t *list, node_func_t free_func);
void list_each(list_t *list, node_func_t func);

#endif /* LIST_H */
