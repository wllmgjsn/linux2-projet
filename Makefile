CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL = client server labo

all: $(ALL)

client: client.o utils.o 
	$(CC) $(CCFLAGS) -o client client.o utils.o

server: server.o utils.o 
	$(CC) $(CCFLAGS) -o server server.o utils.o

labo: labo.o utils.o 
	$(CC) $(CCFLAGS) -o labo labo.o utils.o

client.o: client.c utils.h projet_config.h
	$(CC) $(CCFLAGS) -c client.c

server.o: server.c utils.h projet_config.h
	$(CC) $(CCFLAGS) -c server.c

labo.o: labo.c utils.h projet_config.h
	$(CC) $(CCFLAGS) -c labo.c

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -c utils.c

clean: 
	rm -f $(ALL) *.o