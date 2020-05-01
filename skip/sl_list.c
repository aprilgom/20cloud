#include "sl_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
sl_node* makenode(int lvl,int key,int value);
skiplists* sl_init(){
	srand(time(NULL));
	skiplists* res = (skiplists*)malloc(sizeof(skiplists)); 	
	res->level = 1;
	res->header = makenode(MAX_LEVEL,INT_MIN,0);
	sl_node* nil = makenode(MAX_LEVEL,INT_MAX,0);
	for(int i = 1;i<=MAX_LEVEL;i++){
		res->header->forward[i] = nil;	
	}
	return res;
}

int Search(skiplists* list,int searchKey){
	sl_node* x = list->header;
	for(int i = list->level;i>=1;i--){
		while(x->forward[i]->key < searchKey)
			x = x->forward[i];
	}
	x = x->forward[1];	
	if(x->key == searchKey){
		return x->value;
	}else{
		return INT_MAX;	
	}
}
float randomPercent(){
	return (float)rand()/RAND_MAX;
}
int randomLevel(){
	int lvl = 1;
	while(randomPercent()<0.5&&lvl<MAX_LEVEL){
		lvl = lvl + 1;
	}
	return lvl;
}
sl_node* makenode(int lvl,int key,int value){
	sl_node* res = (sl_node*)malloc(sizeof(sl_node));
	res->key = key;
	res->value = value;
	res->forward = (sl_node**)malloc(sizeof(sl_node*)*(lvl+1)); 
	return res;
}

void Insert(skiplists* list,int searchKey,int newValue){
	sl_node* update[MAX_LEVEL];
	sl_node* x = list->header;
	for(int i = list->level;i>=1;i--){
		while(x->forward[i]->key <= searchKey){
			x = x->forward[i];
		}
		update[i] = x;		
	}
	x = x->forward[1];
	if(x->key == searchKey){
		x->value = newValue;	
	}
	else
	{
		int lvl = randomLevel();
		if(lvl > list->level){
			for(int i = list->level+1;i<=lvl;i++){
				update[i] = list->header;
			}
			list -> level = lvl;
		}
		x = makenode(lvl,searchKey,newValue);
		for(int i = 1;i<=lvl;i++){
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
	}
}
int Delete(skiplists* list,int searchKey){
	sl_node* update[MAX_LEVEL];
	sl_node* x = list->header;
	for(int i = list->level;i>=1;i--){
		while(x->forward[i]->key < searchKey)
			x = x->forward[i];
		update[i] = x;		
	}
	x = x->forward[1];
	if(x->key == searchKey){
		for(int i = 1;i<=list->level;i++){
			if(update[i]->forward[i]!=x)break;
			update[i]->forward[i] = x->forward[i];	
		}
		//free(x);
		free(x->forward);
		free(x);
		while(list->level > 1&&list->header->forward[list->level] == NULL){
			list->level = list->level-1;
		}
		return 1;
	}else{
		return 0;	
	}
}

