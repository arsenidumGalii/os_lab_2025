#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    pid_t child = fork();
    if(child == 0) execl("./sequential_min_max", "sequential_min_max", argv[1], argv[2], NULL);
    else wait(NULL);
    return 0;
}