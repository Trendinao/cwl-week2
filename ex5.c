#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd[2];

	pipe(fd);

	if(fork()){ //parent process
		close(fd[0]);
		write