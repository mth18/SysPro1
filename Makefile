CC=gcc
CFLAGS=-g -Wall

all: myshell.o slow.o

myshell.o: myshell.c myshell.h parse.c parse.h
	$(CC) $(CFLAGS) myshell.c myshell.h parse.c parse.h -o myshell
slow.o: slow.c
	$(CC) $(CFLAGS) slow.c -o slow

run:
	./myshell

.PHONY:

clean: 
	rm *.o
