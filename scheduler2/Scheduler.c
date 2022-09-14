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
		
		if(ReadyQHead != NULL)