#ifndef _LIST_
#define _LIST_

#define list_for_each(pos,head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
#define list_for_each_safe(pos,n,head) \
	for(pos = (head)->next, n=pos->next; pos != (head); \
		pos = n, n = pos->next)
#define CONTAINING_RECORD(address, type, field) \
	((type *)((char*)(address) - offsetof(type,field)))
#define list_entry(address, type, field) \
	CONTAINING_RECORD(address, type, field)


typedef struct _DHEAD {
	struct _DHEAD *next, *prev;
}DHEAD;

typedef struct _DNODE {
	int data;
	DHEAD head;
}DNODE;

void dlist_init(DHEAD*);
void dlist_insert(DHEAD* head,DHEAD* newnode);
void dlist_remove(DHEAD*);

#endif