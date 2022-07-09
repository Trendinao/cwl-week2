#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
	int fd, nwrite;
	char buf[BUFSIZE];

	//if argument number is miss match
	if(argc != 2 ) fprintf(stderr, "usage : %s fi