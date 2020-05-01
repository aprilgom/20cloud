#include "kvsh.h"
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdio.h>

KV_HEAD* kv_new(int hash_size) {
	
	printf("rwlock hash\n");
	KV_HEAD* kvlist = (KV_HEAD*)malloc(sizeof(KV_HEAD));
	if(kvlist == NULL)return NULL;
	kvlist->list = (skiplists**)malloc(sizeof(skiplists)*hash_size);
	kvlist->hash_size = hash_size;
	if(kvlist->list == NULL)return NULL;
	pthread_rwlock_init(&(kvlist->rwlock),NULL);
	for(int i = 0;i<kvlist->hash_size;i++){
		kvlist->list[i] = sl_init();		
	}
	return kvlist;
}

int kv_destroy(KV_HEAD* inp_head){
	
	if(inp_head == NULL)return -1;
	skiplists** list = inp_head->list;	

	for(int i = 0;i<inp_head->hash_size;i++){
		while(list[i]->header->forward[1]->key != INT_MAX){
			Delete(list[i],list[i]->header->forward[1]->key);	
		}	
	}
	free(inp_head);
	return 0;
}

int kv_put(KV_HEAD* inp_head,KV_NODE* kv_pair) {
	
	if(inp_head == NULL)return -1;
	
	int hash_sz = inp_head->hash_size;
	int key = kv_pair->key;
	int value = kv_pair->value;

	skiplists* hlist_entry = inp_head->list[key%hash_sz];

	pthread_rwlock_wrlock(&(inp_head->rwlock));
	Insert(hlist_entry,key,value);
	pthread_rwlock_unlock(&(inp_head->rwlock));
	return 1;
}

KV_NODE* kv_get(KV_HEAD* inp_head, int inp_key) {
	
	if(inp_head == NULL)return NULL;
	
	int hash_sz = inp_head->hash_size;
	skiplists* hlist_entry = inp_head->list[inp_key%hash_sz];
	KV_NODE* ret = NULL;
	ret = (KV_NODE*)malloc(sizeof(KV_NODE));
	ret->key = inp_key;	
	pthread_rwlock_rdlock(&(inp_head->rwlock));
	ret->value = Search(hlist_entry,inp_key);
	pthread_rwlock_unlock(&(inp_head->rwlock));
	if (ret->value != INT_MAX) {
		return ret;
	}else{
		return NULL;
	}
}

int kv_delete(KV_HEAD* inp_head, int inp_key) {

	if (inp_head == NULL)return -1;
	int found = 0;

	int hash_sz = inp_head->hash_size;
	skiplists* hlist_entry = inp_head->list[inp_key%hash_sz];

	pthread_rwlock_wrlock(&(inp_head->rwlock));
	found = Delete(hlist_entry,inp_key);
	pthread_rwlock_unlock(&(inp_head->rwlock));
	if (found)
		return 1;
	else
		return 0;
}
