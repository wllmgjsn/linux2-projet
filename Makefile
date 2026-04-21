CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL = client server

all: $(ALL)

client: client.o utils.o 
	$(CC) $(CCFLAGS) -o client client.o utils.o

server: server.o utils.o 
	$(CC) $(CCFLAGS) -o server server.o utils.o

client.o: client.c utils.h project_config.h
	$(CC) $(CCFLAGS) -c client.c

server.o: server.c utils.h project_config.h
	$(CC) $(CCFLAGS) -c server.c

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -c utils.c

clean: 
	rm -f $(ALL) *.o