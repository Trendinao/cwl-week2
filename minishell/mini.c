#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "getch.h"

#define BUFSIZE 512

int main(int argc, char* argv[]){
	fprintf(stderr, "User Shell >> "); 
	char cmd[BUFSIZE];
	memset(cmd, 0, sizeof(cmd