#include<stdlib.h>
#include "list.h"

void dlist_init(DHEAD* dlist){

	if (dlist == NULL)return;
	dlist->next = dlist;
	dlist->prev = dlist;
}

void dlist_insert(DHEAD* head,DHEAD* newnode){
	//insert next to the head node
	newnode->next = head->next;
	newnode->prev = head;
	head->next->prev = newnode;
	head->next = newnode;
}

void dlist_remove(DHEAD* del){
	//remove current node;
	del->prev->next = del->next;
	del->next->prev = del->prev;
	del->prev = 0;
	del->next = 0;
}

