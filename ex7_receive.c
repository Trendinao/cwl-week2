#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
	int fd, nread;
	char buf[BUFSIZE];

	//if arguments is miss match
	if(argc != 2) f