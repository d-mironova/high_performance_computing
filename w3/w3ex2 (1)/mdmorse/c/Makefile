# $Id: Makefile 12 2008-09-15 20:05:15Z aakurone $

CC=gcc
CFLAGS=-O2 -pg
LDFLAGS=-lm -pg

HEADERS=global.h
OBJECTS= main.o inout.o physical.o neighbourlist.o solve.o forces.o
TARGET=mdmorse

mdmorse: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

inout.o: inout.c $(HEADERS)
	$(CC) $(CFLAGS) -c inout.c

physical.o: physical.c $(HEADERS)
	$(CC) $(CFLAGS) -c physical.c

neighbourlist.o: neighbourlist.c $(HEADERS)
	$(CC) $(CFLAGS) -c neighbourlist.c

solve.o: solve.c $(HEADERS)
	$(CC) $(CFLAGS) -c solve.c

forces.o: forces.c $(HEADERS)
	$(CC) $(CFLAGS) -c forces.c

clean:
	rm -f *.o $(TARGET)

