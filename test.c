#define HAVE_STRUCT_TIMESPEC
#include "kvs.h"
#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_NODES 1000


typedef struct _INSERT_PARAM {
	KV_HEAD* list;
	KV_NODE* kv_pair;
}INSERT_PARAM;


typedef struct _SEARCH_PARAM {
	KV_HEAD* list;
	int key;
}SEARCH_PARAM;

typedef struct _DELETE_PARAM {
	KV_HEAD* list;
	int key;
}DELETE_PARAM;

typedef struct _SEARCH_RANGE_PARAM {
	KV_HEAD* list;
	int keymin,keymax;
}SEARCH_RANGE_PARAM;


void* search(void* data) {
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	SEARCH_PARAM* sp = (SEARCH_PARAM*)data;
	KV_HEAD* kv = sp->list;
	int key = sp->key;
	KV_NODE* p_node;
	DHEAD* p_entry;
	p_node = kv_get(kv, key);
	if (p_node == NULL) {
		printf("key:%d vs node does not exist!\n",key);
		getchar();
		return -1;
	}
	printf("key:%d search finded successfully\n",key);
	return (void*)p_node;
}
/*
void* search_range(void* data) {
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	SEARCH_RANGE_PARAM* srp = (SEARCH_RANGE_PARAM*)data;
	KV_HEAD* kv = srp->list;
	int keymin = srp->keymin;
	int keymax = srp->keymax;
	KV_NODE* p_node;
	DHEAD* p_entry;
	int num_entries=0;
	KV_NODE* p_kvs_nodes = kv_get_range(kv, keymin, keymax, &num_entries);
		printf("fdsad");
	if (num_entries != (100 - 50 + 1)) {
		printf("pid: % d, tid : % d, keymin : % d keymax : %d expactation is not met\n", pid, tid, keymin,keymax);
		getchar();
		return -1;
	}
	printf("search range pid:%d, tid:%d ended successfully\n", pid, tid);
}
*/
void* insert(void* data) {
	
	int* ret;
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	INSERT_PARAM* insert_param = (INSERT_PARAM*)data;
	KV_HEAD* list = insert_param->list;
	KV_NODE* kv_pair = insert_param->kv_pair;
	if (!kv_put(list, kv_pair)) {
		printf("key:%d, value:%d inserted successfully.\n", kv_pair->key, kv_pair->value);
	}else{
		printf("key:%d, value:%d inserted failed.\n", kv_pair->key, kv_pair->value);
	}
	ret = (int*)malloc(sizeof(int));
	*ret = 1;
	return (void*)ret;
}

void* delete(void* data) {
	int* ret;
	ret = (int*)malloc(sizeof(int));
	DELETE_PARAM* dp = (DELETE_PARAM*)data;
	KV_HEAD* kv = dp->list;
	int key = dp->key;
	KV_NODE* p_node;
	DHEAD* p_entry;
	p_node = kv_delete(kv, key);
	if (p_node == NULL) {
		printf("key:%d vs node does not exist!\n", key);
		getchar();
		*ret = -1;
		return ret;
	}
	printf("key:%d deleted successfully\n", key);
	*ret = 0;
	return ret;
}

int main() {

	pthread_t s_thread[100];
	pthread_t i_thread[100];
	pthread_t d_thread[100];
	int joinStatus;
	
	KV_HEAD* my_kv;
	KV_NODE tmpnode[100];
	KV_NODE* search_ret[100];

	INSERT_PARAM tmp_insert_param[100];
	SEARCH_PARAM tmp_search_param[100];
	DELETE_PARAM tmp_delete_param[100];

	my_kv = kv_new();
	if(my_kv == NULL){
		printf("kv create failed");
		getchar();
		return -1;
	}
	for (int i = 0;i < 100;i++) {
		tmpnode[i].key = i;
		tmpnode[i].value = i;
		tmp_insert_param[i].list = my_kv;
		tmp_insert_param[i].kv_pair = &tmpnode[i];
		pthread_create(&i_thread[i], NULL, insert, (void*)&tmp_insert_param[i]);
	}
	for (int i = 0;i < 100;i++) {
		pthread_join(i_thread[i], (void**)&joinStatus);
	}
	for (int i = 0;i < 100;i++) {
		tmp_search_param[i].list = my_kv;
		tmp_search_param[i].key = i;
		pthread_create(&s_thread[i], NULL, search,(void*)&tmp_search_param[i]);
	}
	for (int i = 0;i < 100;i++) {
		pthread_join(s_thread[i], (void**)&search_ret[i]);
	}
	for (int i = 0;i < 100;i++) {
		printf("searched key: %d value: %d \n",search_ret[i]->key,search_ret[i]->value);
	}
	for (int i = 0;i < 100;i++) {
		tmp_delete_param[i].list = my_kv;
		tmp_delete_param[i].key = i;
		pthread_create(&d_thread[i], NULL, delete, (void*)&tmp_delete_param[i]);
	}
	for (int i = 0;i < 100;i++) {
		pthread_join(d_thread[i], (void**)&joinStatus);
	}
	if (my_kv->list.next == &my_kv->list)printf("delete successed\n");
	printf("test is done\n");
	kv_destroy(my_kv);

	getchar();
	
	return 0;
	
}