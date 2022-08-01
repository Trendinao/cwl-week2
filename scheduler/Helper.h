#include <stdbool.h>
#include <pthread.h>
#include "MsgQueue.h"
pthread_cond_t static_cond; 
pthread_mutex_t static_mutex;
bool is_pushed;

/* join structur */
typedef struct _JoinStr JoinStr;
typedef struct _JoinStr{
	pthread_t tid;
	pthread_t parentTid;
	JoinStr* pPrev;
	JoinStr* pNext;
} JoinStr;

/* head for running queue */
Thread*     RunQHead;

/* head and tail for join queue*/
JoinStr* JoinQHead;
JoinStr* JoinQTail;

void* __wrapperFunc(void* arg);

void __thread_wait_handler(int signo);
Thread* __getThread(thread_t tid);
void __thread_wakeup(Thread* pTCB);

void rq_push(Thread *in_TCB);
Thread* rq_search(pthread_t s_tid);
Thread* rq_r