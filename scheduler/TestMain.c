#include <stdio.h>
#include <stdlib.h>

#include "TestCase1.h"
#include "TestCase2.h"
#include "TestCase3.h"

#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"


// #include "Task.h"
// #include "init.h"
// #include "ObjMgr.h"
// #include "Scheduler.h"

void main(int argc, char* argv[])
{
	int TcNum;
	thread_t tid1,tid2,tid3,tid4;

	i