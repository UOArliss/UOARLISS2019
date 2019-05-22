CFLAGS= -W -Wall -g 
PROGS= arlissbot
CC = gcc
OBJECTS= bq.o 

all: $(PROGS)

arlissbot: main.c 
	cc -o arlissbot $^

bq.o: bqueue.h bqueue.c

clean:
	rm -f *~ $(OBJECTS) $(PROGS)
