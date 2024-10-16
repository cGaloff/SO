#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>


int main(){
    pid_t root = getpid();
    int i = 0;
    int *turn;
    int smcid;
    smcid = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | S_IRUSR | S_IWUSR);
    turn = (int *) shmat(smcid,0,0);
    *turn = -1;

    for(i = 0; i < 3; i++){
        if(!fork())
            break;
    }

    if(root == getpid()){

        *turn = 0;
        printf("PADRE [%d] --> TURNO [%d] \n", root, *turn);
        

        for (int j = 0; j < 3; j++)
            wait(NULL);
        
        shmdt(turn);
        shmctl(smcid,IPC_RMID,0);
        
    }else{
        
        while (*turn != i);
        ++*turn;
        printf("HIJO [%d] --> PID [%d] \n", *turn, getpid());
        
    }

    return 0;
}

