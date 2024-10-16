#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main(){
    int pipes[2];
    char buffer[256] = {'0'};
    pipe(pipes);

    printf("PID padre %d \n", getpid());
    write(pipes[1],"MENSAJE RECIBIDO",17);

    if(fork()){
        close(pipes[0]);
        return;
    }

    read(pipes[0],buffer,17);
    printf("PID HIJO %d \n ", getpid());
    printf("MSJ->>> %s", buffer);
    close(pipes[1]);
}