#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct sl_node{
	int key;
	int value;
	struct sl_node **forward;
}sl_node;

typedef struct skiplists{
	int level;
	struct sl_node *header;
}skiplists;

#define MAX_LEVEL 16
void random_init();
sl_node* makenode(int lvl,int key,int value);
skiplists* sl_init();
int Search(skiplists* list,int searchKey);
float randomPercent();
int randomLevel();
sl_node* makenode(int lvl,int key,int value);
void Insert(skiplists* list,int searchKey,int newValue);
int Delete(skiplists* list,int searchKey);

