#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "Helper.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int RunScheduler( void ){
	//run scheduler
	Thread* pCurThread = NULL;
	Thread* pNewThread = NULL;
	
	while(1){
		fflush(stdout);
		
		pCurThread = RunQHead;
		//get running thread's TCB pointer
		
		if(ReadyQHead != NULL){
			//if ready queue is not empty	
			if(pCurThread == NULL) //fprintf(stderr, "running thread's TCB isn't exist (RunScheduler())\n");
			if((pNewThread = ReadyQHead) == NULL){
				//check any TCB is in ready queue
				continue;
				//if ready queue is empty, don't call context switch
			}
		}
		__ContextSwitch(pCurThread, pNewThread);
		//context switch
		
		sleep(TIMESLICE);
	}
}


void __ContextSwitch(Thread* pCurThread, Thread* pNewThread){
	//send running thread to ready queue, pop head thread and run
	//schduler call rq_pop, pass Thread pointer to