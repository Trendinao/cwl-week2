TARGET = test
OBJECTS = testcase.o disk.o fs.o Matrix.o mount.o
SRCS = $(OBJECTS:.o=.c)

CC = gcc
CFLAGS = -g -c
.SUFFIXES : .c .o

$(TARGET) : $(OBJECTS) 
	$(CC) -g -pthread $(OBJECTS) -o $@ -lm
testcase.o : testcase.c fs.h
#	$(CC) $(