#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kvsh.h"

#define MAX_HASH_N		547 
#define NUM_NODES		1000000
#define NUM_THREADS		10	

typedef void (*THREAD_FUNC)(void*);

struct SHARED_STATE_T {
	pthread_mutex_t mu;
	pthread_cond_t	cv;
	int total;
	int num_inited;
	int num_done;
	int start;
};

struct THREAD_STATE_T {
	pthread_t tid;
	int rand_seed;	 /*1: 1-1000000, 2: 1000001-2000000*/
	struct timespec start;
	struct timespec finish;
	int done;
	KV_HEAD* kvs;
};

struct THREAD_ARG_T {
	struct SHARED_STATE_T* ss;
	struct THREAD_STATE_T* ts;
	THREAD_FUNC tf;
};

void *thread_main(void* arg) {
	struct THREAD_ARG_T* thread_arg = arg;
	struct SHARED_STATE_T* ss = thread_arg->ss;
	struct THREAD_STATE_T* ts = thread_arg->ts;

	pthread_mutex_lock(&ss->mu);
	ss->num_inited++;
	if (ss->num_inited >= ss->total) {
		pthread_cond_broadcast(&ss->cv);
	}
	while (!ss->start) {
		pthread_cond_wait(&ss->cv, &ss->mu);
	}
	pthread_mutex_unlock(&ss->mu);

	clock_gettime(CLOCK_REALTIME,&ts->start);
	(thread_arg->tf)((void *)ts);
	clock_gettime(CLOCK_REALTIME,&ts->finish);

	pthread_mutex_lock(&ss->mu);
	ss->num_done++;
	if (ss->num_done >= ss->total) {
		pthread_cond_broadcast(&ss->cv);
	}
	pthread_mutex_unlock(&ss->mu);

	return NULL;
}
void do_benchmark(KV_HEAD *kvs, int num_threads, THREAD_FUNC* tfl) {
	int i, ret;
	double elapsed = 0, num_ops = 0;
	struct SHARED_STATE_T shared;
	struct THREAD_STATE_T* tss;
	struct THREAD_ARG_T* args;

	THREAD_FUNC read_tf = tfl[0];
	THREAD_FUNC write_tf = tfl[1];

	pthread_mutex_init(&shared.mu, NULL);
	pthread_cond_init(&shared.cv, NULL);
	shared.num_inited = 0;
	shared.num_done = 0;
	shared.start = 0;
	shared.total = num_threads;
	
	args = (struct THREAD_ARG_T *)malloc(sizeof(struct THREAD_ARG_T) * num_threads);
	if (args == NULL) {
		printf("args malloc failed\n");
		return;
	}
	memset((void*)args, 0x00, sizeof(struct THREAD_ARG_T) * num_threads);

	tss = (struct THREAD_STATE_T*) malloc(sizeof(struct THREAD_STATE_T) * num_threads);
	if (tss == NULL) {
		printf("tss malloc failed\n");
		free(args);
		return;
	}
	memset((void*)tss, 0x00, sizeof(struct THREAD_STATE_T) * num_threads);

	for (i = 0; i < num_threads * 1/10; i++) {
		args[i].ss = &shared;
		args[i].ts = &tss[i];
		args[i].ts->kvs = kvs;
		args[i].tf = write_tf;

		pthread_create(&args[i].ts->tid, NULL, thread_main, &args[i]);
	}
	for (i = num_threads*1/10; i < num_threads ; i++) {
		args[i].ss = &shared;
		args[i].ts = &tss[i];
		args[i].ts->kvs = kvs;
		args[i].tf = read_tf;

		pthread_create(&args[i].ts->tid, NULL, thread_main, &args[i]);
	}
	pthread_mutex_lock(&shared.mu);
	while (shared.num_inited < num_threads) {
		pthread_cond_wait(&shared.cv, &shared.mu);
	}

	shared.start = 1;
	pthread_cond_broadcast(&shared.cv);
	while (shared.num_done < num_threads) {
		pthread_cond_wait(&shared.cv, &shared.mu);
	}
	pthread_mutex_unlock(&shared.mu);

	for (i = 0; i < num_threads; i++) {
		ret = pthread_join(args[i].ts->tid, NULL);
	}

	// results
	for (i = 0; i < num_threads; i++) {
		elapsed = ((double)tss[i].finish.tv_sec + 1.0e-9*tss[i].finish.tv_nsec) -
		   ((double)tss[i].start.tv_sec + 1.0e-9*tss[i].start.tv_nsec);	
		num_ops += tss[i].done;
	}

	printf("\nelapsed = %f\n",elapsed);
	printf("\nops = %f\n", num_ops / elapsed);

	// free
	free(tss);
	free(args);
}

void search(void* arg) {
	int i;
	struct THREAD_STATE_T* ts = arg;
	KV_NODE* p_node;


	for (i = 0; i < NUM_NODES; i++) {
		p_node = kv_get(ts->kvs, i);

		if (p_node)
			ts->done++;

		//if ((ts->done % 10000) == 0)printf("r");
	}
}

void insert(void* arg) {
	int i, ret;
	struct THREAD_STATE_T* ts = arg;
	KV_NODE node;
	for (i = 0; i < NUM_NODES; i++) {
		node.key = i;
		node.value = i;
		ret = kv_put(ts->kvs, &node);

		ts->done++;

		//if ((ts->done % 10000) == 0)printf("w");
	}
}

int main() {
	KV_HEAD* my_kvs;
	THREAD_FUNC tf[2] = {search,insert};
	// 1. create key/value store
	my_kvs = kv_new(MAX_HASH_N);
	if (my_kvs == NULL) {
		printf("kv create if failed\n");
		getchar();

		return -1;
	}
	KV_NODE node;
	for(int i = 0;i<100000;i++){
		node.key = i;
		node.value = i;
		kv_put(my_kvs, &node);
	}
	do_benchmark(my_kvs, NUM_THREADS,tf);
	kv_destroy(my_kvs);

	printf("test is done!\n");

	return 0;
}
