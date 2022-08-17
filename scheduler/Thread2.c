
#include "Thread.h"
#include "Init.h"
#include "Scheduler.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void* __wrapperFunc(void* arg){
	//!!!!!!!!!! need to confirm !!!!!!!!!!
	fprintf(stderr, "__wrapperFunc() execute\n");	
	
	void* ret;
	WrapperArg* pArg = (WrapperArg*)arg;
	//arg is wrapperArg, need to casting WrapperArg type  	

	sigset_t set;
	int retSig;
	//for handler
	fprintf(stderr, "i will call sigwait (__wrapperFunc())\n");	
	sigemptyset(&set);
	sigaddset(&set, SIGUSR2);
	sigwait(&set, &retSig);
	fprintf(stderr, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	//wait until TCB is pushed in ready queue
	//if TCB is pushed in ready queue, parent thread send SIGUSR2 to child thread to execute handler
	
	//__thread_wait_handler(0);
	//block until thread is ready to run

	void* (*funcPtr)(void*) = pArg->funcPtr;
	void* funcArg = pArg->funcArg;
	fprintf(stderr, "bbbbbbbbbbbbbbbbbbbb\n");
	
	ret = (funcPtr)(funcArg);
	//위에서 세그폴트가 뜨는것 같음. 수정 필요.
	
	fprintf(stderr, "will run func?\n");	
	return ret;
}



int thread_create(thread_t *thread, thread_attr_t *attr, void* (*start_routine)(void *), void *arg){
	//make child thread and push in ready queue
	//!!!!!!!!!! need to confirm !!!!!!!!!!	
	
	pthread_t tmp_tid;
	//for child thread's tid
	
	WrapperArg wrapperArg;
	//for wrapper
	
	wrapperArg.funcPtr = start_routine;
	wrapperArg.funcArg = arg;
	//set wrapper function, argument
	
	fprintf(stderr, "parent create thread right now\n");	
	signal(SIGUSR1, __thread_wait_handler);
	signal(SIGUSR2, __thread_wait_handler); 
	//install SIG2 handler
	
	pthread_create(&tmp_tid, NULL, __wrapperFunc, &wrapperArg);
	//create thread and make to execute __wrapperFunc
	
	fprintf(stderr, "pthread_create called\n");

	Thread* tmp = (Thread*)malloc(sizeof(Thread));
	//make TCB
	tmp->tid = tmp_tid;
	tmp->status = THREAD_STATUS_READY;
	tmp->parentTid = thread_self(); 
	tmp->bRunnable = false;
	pthread_mutex_init(&(tmp->readyMutex), NULL);
	pthread_cond_init(&(tmp->readyCond), NULL);
	tmp->pPrev = tmp->pNext = NULL;
	//set information
	
	rq_push(tmp);
	//push tmp thread in ready queue
	
	*thread = tmp_tid;
	//call back created thread's tid
	printf("parent send signal right now\n");
	pthread_kill(tmp_tid, SIGUSR2);
	//make child thread call handler by sending SIGUSR1
	return 0;
}

int 	thread_join(thread_t thread, void **retval)
{

}


int 	thread_suspend(thread_t tid)
{

}


int	thread_resume(thread_t tid)
{

}




thread_t	thread_self()
{
	return pthread_self();	
}	

void __thread_wait_handler(int signo){
	//call when send thread at ready queue
	
	Thread* tmp;
	fprintf(stderr, "wait_handler is called (__thread_wait_handler())\n");
	
	tmp = __getThread(pthread_self());
	//get caller's TCB pointer
	
	pthread_mutex_lock(&(tmp->readyMutex));
	//lock mutex
	
	fprintf(stderr, "i lock mutex (__thread_wait_handler())\n");
	while(tmp->bRunnable == false){
		fprintf(stderr, "caller's bRunnable is false (__thread_wait_handler())\n");
		pthread_cond_wait(&(tmp->readyCond), &(tmp->readyMutex));
		fprintf(stderr, "receive signal to wake up (__thread_wait_handler())\n");
	}
	//wait until bRunnable be true
	pthread_mutex_unlock(&(tmp->readyMutex));
	//unlock mutex
	fprintf(stderr, "i unlock mutex (__thread_wait_handler())\n");
}

Thread* __getThread(thread_t tid){
	//serach TCB with tid at ready queue and wait queue
	Thread* tmp;

	if((tmp = rq_search(tid)) != NULL){
		fprintf(stderr, "TCB is in ready queue (__getThread())\n");
		return tmp;
	}
	//if TCB is in ready queue
	if((tmp = wq_search(tid)) != NULL){
		fprintf(stderr, "TCB is in wait queue (__getThread())\n");	
		return tmp;
	}
	//if TCB is in wait queue

	return NULL;
	//not exist TCB in ready queue and wait queue
}

void __thread_wakeup(Thread* pTCB){
	//wake up thread with 1st TCB only when it need to run
	
	pthread_mutex_lock(&(pTCB->readyMutex));
	//lock mutex
	pTCB->bRunnable = true;
	pthread_cond_signal(&(pTCB->readyCond));
	//change bRunnable to true, so thread corresponding TCB will be wake up
	pTCB->status = THREAD_STATUS_RUN;
	//set status to run
	pthread_mutex_unlock(&(pTCB->readyMutex));
	//unlock mutex
	

}

void rq_push(Thread *in_TCB){
	//insert in_TCB at ready queue