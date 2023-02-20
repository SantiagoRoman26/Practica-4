#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define tamanio 1000

int main(int argc, char** argv) {
    int rank, size;
    int i, j;
    int matriz[tamanio][tamanio];
    int filas;
    int filasI;
    int diagonal_sum = 0;
    int diagonal_max = 0;
    int global_sum, global_max;
    int max_diagonal, max_diagonal_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    filas = tamanio / size;
    filasI = rank * filas;s
    srand(1);
    for (i = 0; i < tamanio; i++) {
        for (j = 0; j < tamanio; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
    for (i = filasI; i < filasI + filas; i++) {
        diagonal_sum += matriz[i][i];
        if (matriz[i][i] > diagonal_max) {
            diagonal_max = matriz[i][i];
        }
    }
    MPI_Reduce(&diagonal_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        max_diagonal = 0;
        max_diagonal_size = 0;
        for (i = 0; i < tamanio; i++) {
            int sum = 0;
            for (j = 0; j < tamanio; j++) {
                if (i == j) {
                    sum += matriz[i][j];
                }
            }
            if (sum > max_diagonal) {
                max_diagonal = sum;
                max_diagonal_size = i;
            }
        }

        printf("La suma de las diagonales es: %d\n", global_sum);
        printf("El valor máximo de las diagonales es: %d\n", global_max);
        printf("La diagonal con el valor máximo es la diagonal %d\n", max_diagonal_size);
        printf("La diagonal %d es la diagonal más grande\n", max_diagonal_size);
    }

    MPI_Finalize();
    return 0;
}