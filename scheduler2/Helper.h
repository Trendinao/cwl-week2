#include <stdbool.h>
#include <pthread.h>
#include "MsgQueue.h"
pthread_cond_t static_cond; 
pthread_mutex_t static_mutex;
bool is_pushed;

/* join structur */
typedef struct _JoinStr JoinStr;
typedef struct