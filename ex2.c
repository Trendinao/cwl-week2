#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 20
#define PERM 0664

int copy_file(const char* name1, const char* name2){
	int infile, outfile;
	ssize_t nread, nwrite;
	char buf[BUF_SIZE];
	memset(buf, 0, BUF_SIZE);

	if((infile = open(name1, O_RDONLY)) < 0){
		perror("can't open the infile!");
		return(-1);
	}
	
	if((outfile = open(name2, O_WRONLY|O_CREAT|O_APPEND, PERM)) < 0){
	