#include <stdio.h>
#include <termio.h>

int getch(void){
	int ch;
	struct termios buf, save;

	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag 