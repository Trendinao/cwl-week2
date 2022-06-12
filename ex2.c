#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 20
#define PERM 0664

int copy_file(const char* name1, const char* name2){
	int infile, outfile;
	ssize_t nread, nwrite