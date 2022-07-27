
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "getch.h"

#define EOL 1
#define ARG 2
#define AMPERSAND 3
#define SEMICOLON 4
#define INPUT_REDIRECTION 5
#define OUTPUT_REDIRECTION 6
#define MAXARG 512
#define MAXBUF 512
#define FOREGROUND 0
#define BACKGROUND 1


static char inpbuf[MAXBUF], tokbuf[2*MAXBUF], *ptr = inpbuf, *tok = tokbuf;
char *prompt = "Command > ";
static char special[] = {' ','\t','&',';','\n','\0', '>', '<'};
struct sigaction act, act2;

int inarg(char c);
int runcommand(char **cline, int where, int narg, bool is_pipe, char **my_cline, int* p_pipe_fd);
void usr_ls();
int gettok(char **outptr);

int userin(char *p){
	int c, count = 0, i = 0;
    ptr = inpbuf;
    tok = tokbuf;
    printf("%s", p);
    bool double_tab = false;

	while(1){
        if((c = getch()) == EOF) {
			//getch or getchar
            printf("eof = %c\n", c);
            return (EOF);
        }
		
		if(c == 27){
			//if typed arrow key
			if((c = getch()) == 91){
				c = getch();
				if(c == 65 || c == 66 || c == 67 || c == 68) continue;
			}
		}
		
        if (count < MAXBUF){
			//insert c at inpbuf one by one
			if(c == 127){
				//if c is back space
				if(count > 0){
					count--;
					inpbuf[count] = '\0';
					fprintf(stderr, "\b \b");
				}
			}
			else inpbuf[count++] = c;
			//if c isn't back space, insert inpbuf
			
			if(c == '\t'){
				//if c is tap
				char *tmp[10];
				int tmp_narg = 0, same_count = 0, same_size;
				int tmp_type;
				//ptr = inpbuf, tok = tokbuf;
				char same_list[10][256];
				bool flag = false;
				int len = 0;

				count--;
				inpbuf[count] = '\n';
				ptr = inpbuf, tok = tokbuf;
				
					//if first tab, get token
					do{
						tmp_type = gettok(&tmp[tmp_narg]);
						if(tmp_narg < MAXARG) tmp_narg++;
					}while(tmp_type == ARG);
					tmp_narg--;
					len = strlen(tmp[tmp_narg-1]);

				struct dirent* dentry;
				DIR* dirp;
				char cwd[50];

				getcwd(cwd, sizeof(cwd));
				fprintf(stderr, "\n");
				
				if(!double_tab){
					//if first tab, get current working directory 
					if((dirp = opendir(cwd)) == NULL) perror("open directory");
				}
				else{
					//if double tab, get token (it's user input directory)
					if((dirp = opendir(tmp[tmp_narg-1])) == NULL) perror("open directory");
				}
				while((dentry = readdir(dirp)) != NULL){
					if(!double_tab){
						//if first tab, compare token with d_name
						if(strncmp(tmp[tmp_narg-1], dentry->d_name, len) ==0) flag = true;
						else flag = false;

						if(len < strlen(dentry->d_name) && flag){
							strncpy(same_list[same_count], dentry->d_name, sizeof(same_list[same_count]));
							same_count++;
						}
					}else{
						//if double tab, print d_name at terminal
						if(strcmp(dentry->d_name, ".") != 0 && strcmp(dentry->d_name, "..") != 0) 
							fprintf(stderr, "%s ", dentry->d_name);
					}
				}
				if(!double_tab){
					//if first tab, insert same character at inpbuf
					if(same_count > 0){
						int i = 0;
						int j = 0;
						same_size = strlen(same_list[0]);
						if(same_count == 1){ fprintf(stderr, "%s", same_list[0]); }
						else{
							flag = true;
							do{
								for(i = 0; i < same_count; i++){
									for(j = i + 1; j < same_count; j++){