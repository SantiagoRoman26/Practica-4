#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define Filas 1000
#define Columnas 1000

int main(int argc, char** argv) {

    int size, rank, i, j;
    int numero , countL = 0, countG = 0;
    int matriz[Filas][Columnas];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int tamanio = Filas / size;
    printf("-");
    if (rank == 0) {
        printf("Enter the number to find: ");
        scanf("%d", &numero);
        for (i = 0; i < Filas; i++) {
            for (j = 0; j < Columnas; j++) {
                matriz[i][j] = rand() % 100;
            }
        }
    }

    MPI_Bcast(&numero, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int local_Filas[tamanio][Columnas];
    MPI_Scatter(matriz, tamanio * Columnas, MPI_INT, local_Filas, tamanio * Columnas, MPI_INT, 0, MPI_COMM_WORLD);
    for (i = 0; i < tamanio; i++) {
        for (j = 0; j < Columnas; j++) {
            if (local_Filas[i][j] == numero) {
                countL++;
            }
        }
    }

    MPI_Reduce(&countL, &countG, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Cantidad de veces que el numero %d se encontro en la matriz: %d\n", numero, countG);
    }

    MPI_Finalize();

    return 0;
}