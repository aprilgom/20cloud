#define HAVE_STRUCT_TIMESPEC
#include "kvs.h"
#include "list.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<windows.h>
#define BIG_RAND(n) (int)(((double)((rand()<<15) | rand())) / (((RAND_MAX<<15) | RAND_MAX) + 1) * (n))
#define TEST_NUM 1000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct _TST_PARAM{
	KV_HEAD* list;
}TST_PARAM;

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

void swap(int* a,int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void shuffle(int* arr,int n){
	int rnd = 0;
	for(int i = 0;i<n;i++){
		rnd = BIG_RAND(n);
		swap(&arr[i],&arr[rnd]);
	}
}
void init_seq_arr(int* arr,int n){
	for(int i = 0;i<n;i++){
		arr[i]=i;
	}
}
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

void* seq_write(void* data){
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	TST_PARAM* param = (TST_PARAM*)data;	
	KV_HEAD* sq_kv = param->list; 
	for(int i = 0;i<TEST_NUM;i++){
		KV_NODE* new_node;
		new_node = (KV_NODE*)malloc(sizeof(KV_NODE));
		new_node->key = i;
		new_node->value = i;
		kv_put(sq_kv,new_node);
	}
}

void* seq_read(void* data){
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	TST_PARAM* param = (TST_PARAM*)data;	
	KV_HEAD* sq_kv = param->list; 
	for(int i = 0;i<TEST_NUM;i++){
		kv_get(sq_kv,i);
	}
}


void* rnd_write(void* data){
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	TST_PARAM* param = (TST_PARAM*)data;	
	KV_HEAD* sq_kv = param->list; 
	int rnd_arr[TEST_NUM];
	init_seq_arr(rnd_arr,TEST_NUM);
	shuffle(rnd_arr,TEST_NUM);
	for(int i = 0;i<TEST_NUM;i++){
		KV_NODE* new_node;
		new_node = (KV_NODE*)malloc(sizeof(KV_NODE));
		new_node->key = rnd_arr[i];
		new_node->value = rnd_arr[i];
		kv_put(sq_kv,new_node);
	}
}


void* rnd_read(void* data){
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	TST_PARAM* param = (TST_PARAM*)data;	
	KV_HEAD* sq_kv = param->list; 
	int rnd_arr[TEST_NUM];
	init_seq_arr(rnd_arr,TEST_NUM);
	shuffle(rnd_arr,TEST_NUM);
	KV_NODE* res;
	for(int i = 0;i<TEST_NUM;i++){
		res = kv_get(sq_kv,rnd_arr[i]);
	}
}

int main() {
	srand((unsigned int)time(NULL));
	time_t start,end;
	double result;
	pthread_t seq_r_thread[8];
	pthread_t seq_w_thread[8];
	pthread_t rnd_r_thread[8];
	pthread_t rnd_w_thread[8];
	int joinStatus;
	
	TST_PARAM seq_param[8];
	TST_PARAM rnd_param[8];
	//sequential write
	for(int t_i = 0;t_i<8;t_i++){
		seq_param[t_i].list = kv_new();
		pthread_create(&seq_w_thread[t_i], NULL, seq_write, (void*)&seq_param[t_i]);
	}
	Sleep(2000);
	start = time(NULL);
	pthread_cond_broadcast(&cond);
	for(int t_i = 0;t_i<8;t_i++){
		pthread_join(seq_w_thread[t_i],NULL);	
	}	
	end = time(NULL);
	printf("sequential write : %f seconds\n",(double)end - start);

	//sequential read
	for(int t_i = 0;t_i<8;t_i++){
		pthread_create(&seq_r_thread[t_i], NULL, seq_read, (void*)&seq_param[t_i]);
	}
	Sleep(2000);
	start = time(NULL);
	pthread_cond_broadcast(&cond);
	for(int t_i = 0;t_i<8;t_i++){
		pthread_join(seq_r_thread[t_i],NULL);	
	}	
	end = time(NULL);
	printf("sequential read : %f seconds\n",(double)end - start);

	KV_NODE* res;
	//random write
	for(int t_i = 0;t_i<8;t_i++){
		rnd_param[t_i].list = kv_new();
		pthread_create(&rnd_w_thread[t_i], NULL, rnd_write, (void*)&rnd_param[t_i]);
	}
	Sleep(2000);
	start = time(NULL);
	pthread_cond_broadcast(&cond);
	for(int t_i = 0;t_i<8;t_i++){
		pthread_join(rnd_w_thread[t_i],NULL);	
	}	
	end = time(NULL);
	printf("random write : %f seconds\n",(double)end - start);

	
	//random read
	for(int t_i = 0;t_i<8;t_i++){
		pthread_create(&rnd_r_thread[t_i], NULL, rnd_read, (void*)&rnd_param[t_i]);
	}
	Sleep(2000);
	start = time(NULL);
	pthread_cond_broadcast(&cond);
	for(int t_i = 0;t_i<8;t_i++){
		pthread_join(rnd_r_thread[t_i],NULL);	
	}	
	end = time(NULL);
	printf("random read : %f seconds\n",(double)end - start);
	return 0;
}