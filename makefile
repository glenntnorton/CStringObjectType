CC = gcc
CFLAGS = -g -Wall
LDFLAGS =
LIBS =

OBJS = str.o String.o

str : 	$(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

str.o : String.h

clean:
	rm -f *.o


