CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL = client server

all: $(ALL)

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -c utils.c

clean: 
	rm -f $(ALL) *.o