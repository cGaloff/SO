#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef struct data
{
    int n;
    int id;
} Data;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: program.a file_name\n");
        return EXIT_FAILURE;
    }

    FILE *f;
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error al abrir el archivo\n");
        return EXIT_FAILURE;
    }

    int fd[2];
    pipe(fd); //tubería creada
    pid_t root = getpid();
    int i;
    int v_size;
    fscanf(f, "%d", &v_size);
    int *vec = (int *)malloc(sizeof(int) * v_size);

    for(int j = 0; j < v_size; j++){
        fscanf(f, "%d", &vec[j]);
    }

    for (i = 0; i < 3; i++)
    {
        if (!fork())
            break;
    }

    Data data_handler;

    if (root == getpid())
    {
        close(fd[1]);

        while(read(fd[0], &data_handler, sizeof(data_handler))){
            switch (data_handler.id)
            {
            case 0:
                printf("Cantidad de numeros impares: %d\n", data_handler.n);
                break;
            case 1:
                printf("Cantidad de hijos pares: %d\n", data_handler.n);
                break;
            case 2:
                printf("El promedio de los numeros es: %d\n", data_handler.n);
                break;
            default:
                printf("Error\n");
                return EXIT_FAILURE;
                break;
            }
        }

        for(int j = 0; j < 3; j++)
            wait(NULL);
        close(fd[0]);    
        }
    else
    {
        data_handler.id = i;
        close(fd[0]);
        switch (i)
        {
        case 0:
        {
            int n_impares = 0;
            for (int j = 0; j < v_size; j++)
            {
                if (vec[j] % 2 == 1)
                {
                    n_impares++;
                }
            }

            data_handler.n = n_impares;
            write(fd[1], &data_handler, sizeof(data_handler));
            close(fd[1]);
            break;
        }
        case 1:
        {
            int n_pares = 0;
            for (int j = 0; j < v_size; j++)
            {
                if (vec[j] % 2 == 0)
                {
                    n_pares++;
                }
            }
            data_handler.n = n_pares;
            write(fd[1], &data_handler, sizeof(data_handler));
            close(fd[1]);
        }
        case 2:{
            int sum = 0;
            int prom;
            for(int j = 0; j < v_size; j++){
                sum+=vec[j];
            }
            prom = sum/v_size;
            data_handler.n = prom;
            write(fd[1], &data_handler, sizeof(data_handler));
            close(fd[1]);
        }
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}