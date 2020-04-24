#define ARRAY_SIZE(n) (sizeof((n))/sizeof((n)[0]))
#define	hash_init(hashtable) __hash_init(hashtable,ARRAY_SIZE(hashtable)) 
#define HLIST_HEAD_INIT {.first = NULL} 
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
#define DEFINE_HASHTABLE(name,n)\
	hlist_head name[n] = {[0 ... n-1] = HLIST_HEAD_INIT}
#define hash_add(hashtable,node,key) \
	hlist_add_head(node,&hashtable[key%ARRAY_SIZE(hashtable)])

struct hlist_head{
	struct hlist_node *first;
}hlist_head;

struct hlist_node{
	struct hlist_node *next,**pprev;
}hlist_node;


static inline void __hash_init(hlist_head *ht,unsigned int sz){
	for(int i = 0;i<sz;i++){
		INIT_HLIST_HEAD(&ht[i]);
	}
}

static inline void hlist_add_head(hlist_node *n,hlist head *h){
	hlist_node *first = h->first;
	n->next = first;
	if(first){
		first->pprev = &n->next;
	}
	h->first = n;
	n->pprev = &h->first;
}

static inline void hlist_remove(hlist_node *n){
	hlist_node *next = n->next;
	hlist_node **prev = n->prev;
	*pprev = next;
	if(next)next->pprev = pprev
}

