#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void signalHandler(int sig){printf("RECIBIDA SENAL");}

int main(){
    signal(SIGIO,&signalHandler);
    while (1)
    {
        printf("Hola mundo \n");
        sleep(2);
    }
    
    return 0;
}