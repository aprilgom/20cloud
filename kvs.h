#ifndef _KVS_
#define _KVS_

#include"list.h"
#include<pthread.h>

typedef struct _KV_HEAD {
	pthread_mutex_t mu;
	DHEAD list;
}KV_HEAD;


typedef struct _KV_NODE {
	int key;
	int value;
	DHEAD list;
}KV_NODE;


KV_HEAD* kv_new();
int kv_destroy(KV_HEAD* entry);
int kv_put(KV_HEAD* node, KV_NODE* kv_pair);
KV_NODE* kv_get(KV_HEAD* node, int key);
KV_NODE* kv_get_range(KV_HEAD* node, int keymin, int keymax,int* num_entries);
int kv_delete(KV_HEAD* node, int key);
#endif


