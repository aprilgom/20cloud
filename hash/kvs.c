#include "kvs.h"
#include "list.h"
#include<stdlib.h>
#include<string.h>
KV_HEAD* kv_new() {
	KV_HEAD* kvlist = (KV_HEAD*)malloc(sizeof(KV_HEAD));
	if(kvlist == NULL)return NULL;
	pthread_mutex_init(&(kvlist->mu), NULL);
	dlist_init(&kvlist->list);
	return kvlist;
}

int kv_destroy(KV_HEAD* inp_head){
	
	if(inp_head == NULL)return -1;
	
	DHEAD* p_entry,*tmp;
	KV_NODE* p_kv_node;
	
	
	list_for_each_safe(p_entry,tmp,&inp_head->list){
		p_kv_node = list_entry(p_entry,KV_NODE,list);
		dlist_remove(&p_kv_node->list);
		free(p_kv_node);
	}
	
	free(inp_head);
	
	return 0;
}

int kv_put(KV_HEAD* inp_head,KV_NODE* kv_pair) {
	
	if(inp_head == NULL)return -1;
	
	int found = 0;
	DHEAD* p_entry;
	KV_NODE* p_kv_node;
	
	int is_zero = 0;
	DHEAD* inp_h = &inp_head->list;

	pthread_mutex_lock(&(inp_head->mu));
	list_for_each(p_entry, &inp_head->list) {
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
		dlist_insert(&inp_head->list,&p_kv_node->list);
	}
	pthread_mutex_unlock(&(inp_head->mu));
	return found;
}

KV_NODE* kv_get(KV_HEAD* inp_head, int inp_key) {
	
	if(inp_head == NULL)return NULL;
	
	int found = 0;
	DHEAD* p_entry;
	KV_NODE* p_kv_node = NULL,*ret = NULL;
	
	ret = (KV_NODE*)malloc(sizeof(KV_NODE));
	pthread_mutex_lock(&(inp_head->mu));
	list_for_each(p_entry,&inp_head->list){
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

KV_NODE* kv_get_range(KV_HEAD* inp_head, int keymin, int keymax,int* num_entries) {
	
	if(inp_head == NULL)return NULL;
	
	DHEAD* p_entry;
	KV_NODE* p_kv_node, *p_temp_node,*ret;
	
	ret = (KV_NODE*) malloc(sizeof(KV_NODE));
	dlist_init(&ret->list);
	
	list_for_each(p_entry,&inp_head->list){
		
		p_kv_node = list_entry(p_entry,KV_NODE,list);
		
		if(p_kv_node->key >= keymin && p_kv_node->key <= keymax){
			p_temp_node = (KV_NODE*)malloc(sizeof(KV_NODE));
			p_temp_node->key = p_kv_node->key;
			p_temp_node->value = p_kv_node->value;
			dlist_insert(&ret->list ,&p_temp_node->list);
			*num_entries+=1;
		}
		
	}
	if(*num_entries == 0){
		free(ret);
		return NULL;
	}
	return ret;
}

int kv_delete(KV_HEAD* inp_head, int inp_key) {

	if (inp_head == NULL)return -1;
	int found = 0;
	DHEAD* p_entry, * tmp;
	KV_NODE* p_kv_node;
	pthread_mutex_lock(&(inp_head->mu));
	list_for_each_safe(p_entry, tmp, &inp_head->list) {
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
