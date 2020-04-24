#include"test_define.h"
#ifdef _RWLOCK_
#include"kvs.h"
#include"list.h"
#include<pthread.h>

typedef struct _KV_HASH_HEAD {
	pthread_rwlock_t rwlock;
	DHEAD* list;
	int hash_size;
}KV_HASH_HEAD;

KV_HASH_HEAD* kv_hash_new(int hash_size);
int kv_hash_destroy(KV_HASH_HEAD* entry);
int kv_hash_put(KV_HASH_HEAD* node, KV_NODE* kv_pair);
KV_NODE* kv_hash_get(KV_HASH_HEAD* node, int key);
int kv_hash_delete(KV_HASH_HEAD* node, int key);
#endif
