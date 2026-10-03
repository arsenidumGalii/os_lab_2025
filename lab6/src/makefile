CC=gcc
CFLAGS=-I. 

all : utils.o client server

clean : 
	rm server client utils.o
client : client.c
	$(CC) utils.o client.c -o client
server : server.c
	$(CC) utils.o server.c -o server
utils.o : utils.h utils.c
	$(CC) -c utils.c $(CFLAGS)
demonstrate:
	./server --port 20001 --tnum 2 > /dev/null 2>&1 &
	./server --port 20002 --tnum 2 > /dev/null 2>&1 &
	./client --k 10 --mod 1000 --servers list_servers.txt 
	killall server