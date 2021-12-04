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
	