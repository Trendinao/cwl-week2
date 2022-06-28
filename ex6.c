
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>

#define TIMER_MSG "Received Timer Interrupt.\n"

bool flag = false;
static void time_hander();
static void int_hander();
static int set_handler();
static int setperiodic();
timer_t timerid;


static void time_handler(){
	printf("%s",TIMER_MSG);
}

static void int_handler(){
	struct itimerspec tmp;

	timer_gettime(timerid, &tmp);
	flag = !flag;
	
	if(flag){
		tmp.it_interval.tv_sec = 3;
	}
	else{
		tmp.it_interval.tv_sec = 5;
	}

	if((timer_settime(timerid, 0, &tmp, NULL)) < 0) perror("failed to set timer");
	printf("\nflag is %d, it_interval.tv_sec is %ld\n", flag, tmp.it_interval.tv_sec); 
}

static int set_handler(){
	struct sigaction act1, act2;

	act1.sa_flags = 0;
	act1.sa_sigaction = time_handler;

	act2.sa_flags = 0;
	act2.sa_sigaction = int_handler;

	if(sigaction(SIGALRM, &act1, NULL) == -1) return -1;
	if(sigaction(SIGINT, &act2, NULL) == -1) return -1;