CC=gcc
CFLAGS=-I.

all : find_min_max.o utils.o parallel_min_max process_memory parallel_sum zombie

find_min_max.o :  find_min_max.h find_min_max.c
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)
utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)
parallel_min_max : find_min_max.h find_min_max.o utils.o utils.h parallel_min_max.c
	$(CC) -o parallel_min_max parallel_min_max.c find_min_max.o utils.o
clean : 
	rm utils.o find_min_max.o process_memory parallel_min_max parallel_sum zombie
process_memory : process_memory.c
	$(CC) -o process_memory process_memory.c
parallel_sum : utils.h
	$(CC) -o parallel_sum parallel_sum.c utils.o
zombie : zombie.c
	$(CC) zombie.c -o zombie