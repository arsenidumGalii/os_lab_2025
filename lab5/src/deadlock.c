#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

void do_first_thing(){
    pthread_mutex_lock(&mut1);
    printf("I locked first mutex! Now I want to sleep...\n");
    usleep(2000000);
    printf("I wake up! Now time to play with second mutex!\n");
    fflush(0);
    pthread_mutex_lock(&mut2);
    printf("That was funny!\n");
}

void do_second_thing(){
    pthread_mutex_lock(&mut2);
    printf("I locked second mutex! Now I want to sleep...\n");
    usleep(2000000);
    printf("I wake up! Now time to play with first mutex!\n");
    fflush(0);
    pthread_mutex_lock(&mut1);
    printf("That was funny!\n");
}

int main(int argc, char**argv){
    pthread_t first, second;
    pthread_create(&first, NULL, (void*) do_first_thing, NULL);
    pthread_create(&second, NULL, (void*) do_second_thing, NULL);
    pthread_join(first, NULL);
    pthread_join(second, NULL);
    return 0;
}