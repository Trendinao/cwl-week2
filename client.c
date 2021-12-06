#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define maxline 100
//#define name_len 20

char *EXIT_STRING = "exit";
int tcp_connect(int af, char *servip, unsigned short port);
void errquit(char *mesg){ perror(mesg); exit(1); }

int main(int argc, char *argv[]){
	char file_name[maxline];
	int maxfdp1;
	int s, nbyte, fd;
	int namelen;
	fd_set read_fds;

	if(argc != 3){
		printf("usage : %s server_ip port filename\n", argv[0]);
		exit(1);
	}

	s = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
	if(s == -1) errquit("