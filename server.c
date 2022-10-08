
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 100
#define max_sock 1024

char *EXIT_STRING = "exit";
char *START_STRING = "connected to char_server\n";
int maxfdp1;
int num_chat = 0;
int clisock_list[max_sock];
int listen_sock;

void addclient(int s, struct sockaddr_in *newcliaddr);
int getmax();
void removeclient(int s);
int tcp_listen(int host, int sort, int backlog);
void errquit(char *mesg){
	perror(mesg);
	exit(1);
}

int main(int argc, char *argv[]) {
	struct sockaddr_in cliaddr;
	char buf[BUFSIZE];
	int i, j, nbyte, accp_sock, fd, fd2;
	int addrlen = sizeof(struct sockaddr_in);
	fd_set read_fds;

	if (argc != 2) {
		//if lack arguments
		printf("usage : %s port\n", argv[0]);
		exit(1);
	}

	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	while (1) {
		FD_ZERO(&read_fds);
		FD_SET(listen_sock, &read_fds);
		//add socket fd to read_fds

		char file_name[BUFSIZE];
		memset(file_name, 0x00, BUFSIZE);