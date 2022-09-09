TARGET = test
OBJECTS = Init.o MsgQueue.o Scheduler.o Thread.o TestMain.o TestCase1.o TestCase2.o TestCase3.o TestCase4.o 
SRCS = $(OBJECTS:.o=.c)

CC = gcc
CFLAGS = -g -c
.SUFFIXES : .c .o

$(TARGET) : $(OBJECTS) 
	$(CC) -g -pthread $(OBJECTS) -o $@
Init.o : Init.c Helper.h
#	$(CC) $(CFLAGS) $*.c -o $@
MsgQueue.o : MsgQueue.c 