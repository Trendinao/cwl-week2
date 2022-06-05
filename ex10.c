#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int ncount;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* do_loop(void *data){
	int i;
	for(i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex);
		printf("loop : %d\n", ncount);
		ncount++;
		if(i == 10) return;

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void* do_loop2(void *data){
	int i;
	for(i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex);
		printf("loop2 : %d\n", ncount);
		ncount++;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
}

int main(){
	int thr_id;
	pthread_t p_thread[2];
	int status;
	int a = 1;

	ncount = 0;
	thr_id = pthread_create(&p_t