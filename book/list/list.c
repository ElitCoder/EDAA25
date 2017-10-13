#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void new_list(list_t** list, void* data)
{
	list_t*	h = malloc(sizeof(list_t));
	h->next = NULL;
	h->data = data;
		
	*list = h;
}

void insert_last(list_t** list, void* data)
{	
	list_t*	p;
	list_t*	h = *list;
	
	if (h == NULL) {
		new_list(list, data);
		
		return;
	}
	
	while (h != NULL) {
		p = h;
		h = h->next;
	}
	
	h = malloc(sizeof(list_t));
	h->next = NULL;
	h->data = data;
	
	p->next = h;
}

void* remove_first(list_t** list)
{
	printf("entering\n");
	
	void*	data;
	list_t*	tmp;
	
	if (*list == NULL)
		return NULL;
		
	printf("list was not null\n");
		
	data = (*list)->data;
	tmp = (*list)->next;
	
	printf("saved information\n");
	
	free(*list);
	
	printf("freed\n");
	
	*list = tmp;
	
	return data;
}

void free_list(list_t** list)
{
	list_t*	next = *list;
	list_t*	tmp;
	
	while (next != NULL) {
		tmp = next;
		next = next->next;
		
		free(tmp);
	}
	
	*list = NULL;
}

size_t length(list_t* list)
{
	size_t	len = 0;
	
	if (list == NULL)
		return len;
	
	while (list != NULL) {
		len++;
		list = list->next;
	}
		
	return len;
}