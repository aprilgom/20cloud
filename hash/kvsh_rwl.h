#include"list.h"
#include<pthread.h>

typedef struct _KV_HEAD {
	pthread_rwlock_t rwlock;
	DHEAD* list;
	int hash_size;
}KV_HEAD;

typedef struct _KV_NODE {
	int key;
	int value;
	DHEAD list;
}KV_NODE;

KV_HEAD* kv_new(int hash_size);
int kv_destroy(KV_HEAD* entry);
int kv_put(KV_HEAD* node, KV_NODE* kv_pair);
KV_NODE* kv_get(KV_HEAD* node, int key);
int kv_delete(KV_HEAD* node, int key);
