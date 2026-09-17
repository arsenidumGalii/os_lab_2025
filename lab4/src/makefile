CC=gcc
CFLAGS=-I.

find_min_max :  find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)
utils : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)
parallel_min_max : find min_max.h find_min_max.o utils.o utils.h
	$(CC) -o parallel_min_max.c find_min_max.o utils.o
clean : 
	rm utils.o find_min_max.o process_memory parallel_min_max parallel_sum
process_memory : 
	$(CC) -o process_memory process_memory.c
parallel_sum : utils.h
	$(CC) -o parallel_sum parallel_sum.c utils.o
all : utils.h find_min_max.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)
	$(CC) -o parallel_min_max.c find_min_max.o utils.o
	$(CC) -o parallel_sum parallel_sum.c utils.o
	$(CC) -o process_memory process_memory.c