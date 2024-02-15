CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o student.o stack.o
EXEC=prog.exe
RM=rm -rf 

#The first rule is invoked by default
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

stack.o: stack.c stack.h common.h
	$(CC) $(CFLAGS) -c stack.c

student.o: student.c student.h stack.h
	$(CC) $(CFLAGS) -c student.c

main.o: main.c student.h stack.h common.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) *.o *.exe

