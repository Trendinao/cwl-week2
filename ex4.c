#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
int n=0;

void handler(int signum){
	printf("signal %d recieved\n", 