#include "test_define.h"
#ifdef _MUTEX_
#include "kvs.h"
#include "kvsh.h"
#include "list.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

KV_HASH_HEAD* kv_hash_new(int hash_size) {
	printf("general kv_hash\n");
	KV_HASH_HEAD* kvlist = (KV_HASH_HEAD*)malloc(sizeof(KV_HASH_HEAD));
	if(kvlist == NULL)return NULL;
	kvlist->list = (DHEAD*)malloc(sizeof(DHEAD)*hash_size);
	kvlist->hash_size = hash_size;
	if(kvlist->list == NULL)return NULL;
	pthread_mutex_init(&(kvlist->mu), NULL);
	for(int i = 0;i<kvlist->hash_size;i++){
		dlist_init(&(kvlist->list[i]));			
	}
	return kvlist;
}

int kv_hash_destroy(KV_HASH_HEAD* inp_head){
	
	if(inp_head == NULL)return -1;
	
	DHEAD* p_entry,*tmp;
	KV_NODE* p_kv_node;
	
	for(int i = 0;i<inp_head->hash_size;i++){
		list_for_each_safe(p_entry,tmp,&(inp_head->list[i])){
			p_kv_node = list_entry(p_entry,KV_NODE,list);
			dlist_remove(&p_kv_node->list);
			free(p_kv_node);
		}
	}
	
	free(inp_head);
	
	return 0;
}

int kv_hash_put(KV_HASH_HEAD* inp_head,KV_NODE* kv_pair) {
	
	if(inp_head == NULL)return -1;
	
	int found = 0;
	DHEAD* p_entry;
	KV_NODE* p_kv_node;
		
	int is_zero = 0;
	int hash_sz = inp_head->hash_size;
	int key = kv_pair->key;
	DHEAD* hlist_entry = &(inp_head->list[key%hash_sz]);

	pthread_mutex_lock(&(inp_head->mu));
	list_for_each(p_entry, hlist_entry ) {
		p_kv_node = list_entry(p_entry, KV_NODE, list);
		if (p_kv_node->key == kv_pair->key) {
			found = 1;
			p_kv_node->value = kv_pair->value;
		}
		break;
	}
	
	
	if(!found){
		p_kv_node = (KV_NODE*)malloc(sizeof(KV_NODE));
		p_kv_node->key = kv_pair->key;
		p_kv_node->value = kv_pair->value;
		dlist_init(&p_kv_node->list);
		dlist_insert(hlist_entry,&p_kv_node->list);
	}
	pthread_mutex_unlock(&(inp_head->mu));
	return found;
}

KV_NODE* kv_hash_get(KV_HASH_HEAD* inp_head, int inp_key) {
	
	if(inp_head == NULL)return NULL;
	
	int hash_sz = inp_head->hash_size;
	DHEAD* hlist_entry = &(inp_head->list[inp_key%hash_sz]);

	int found = 0;
	DHEAD* p_entry;
	KV_NODE* p_kv_node = NULL,*ret = NULL;
	
	ret = (KV_NODE*)malloc(sizeof(KV_NODE));
	pthread_mutex_lock(&(inp_head->mu));
	list_for_each(p_entry,hlist_entry){
		p_kv_node = list_entry(p_entry,KV_NODE,list);
		if(p_kv_node->key == inp_key){
			found = 1;
			break;
		}
	}
	pthread_mutex_unlock(&(inp_head->mu));
	if (found) {
		memcpy((void*)ret, (void*)p_kv_node, sizeof(KV_NODE));
		return ret;
	}else{
		return NULL;
	}
}

int kv_hash_delete(KV_HASH_HEAD* inp_head, int inp_key) {

	if (inp_head == NULL)return -1;
	int found = 0;

	int hash_sz = inp_head->hash_size;
	DHEAD* hlist_entry = &(inp_head->list[inp_key%hash_sz]);

	DHEAD* p_entry, * tmp;
	KV_NODE* p_kv_node;
	pthread_mutex_lock(&(inp_head->mu));

	list_for_each_safe(p_entry, tmp, hlist_entry) {
		p_kv_node = list_entry(p_entry, KV_NODE, list);
		if (p_kv_node->key == inp_key) {
			found = 1;
			dlist_remove(&p_kv_node->list);
			free(p_kv_node);
		}
		
	}
	pthread_mutex_unlock(&(inp_head->mu));
	if (found)
		return 1;
	else
		return 0;
}
#endif
