
//#define RW

#ifdef RW
#define _RWLOCK_ 
#else
#define _MUTEX_
#endif

