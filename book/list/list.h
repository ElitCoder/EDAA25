#ifndef LIST_H
#define LIST_H

typedef struct list_t list_t;

struct list_t {
	list_t*	next;
	void*	data;
};

void insert_last(list_t** list, void* data);
void free_list(list_t** list);
void* remove_first(list_t** list);
size_t length(list_t* list);

#endif