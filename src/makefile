#CC = gcc
CC = clang
CFLAGS = -g -Wall
INCLUDES = -I../include
LFLAGS = -L../lib
LIBS = -lm
OBJS = band.o utils.o

.PHONY: depend clean

all: particle_box test

particle_box: particle_box.o $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o particle_box particle_box.o $(OBJS) $(LIBS)

test: test.o $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o test test.o $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm *.o particle_box test
