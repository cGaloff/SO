#include <stdio.h>

int main(){
    FILE *f;
    f = fopen("datos.txt","a");
    if(f == NULL){
        perror("ERROR AL ABRIR");
        return 1;
    }else{
        printf("ABRIÓ CORRECTAMENTE");
    }
    fclose(f);
    return 0;
}