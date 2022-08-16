
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