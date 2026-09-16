#include <stdio.h>
#include <unistd.h>

int main(){
    while(1){
        pid_t zombie = fork();
        if(zombie == 0) {puts("ZOMBIES ARE MOVING!!!"); exit(0);}
        else if(zombie == -1) {puts("ZOMBIES ARE GONE!!!"); exit(0);}
    }
}