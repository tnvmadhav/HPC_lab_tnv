#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int matrix_size, num_threads;
long **A, **B, **C,**D;

void allocate_matrix() {
    int i, j, num=0;

    // Allocate Memory
    A = (long **) malloc(matrix_size * sizeof(long *));
    B = (long **) malloc(matrix_size * sizeof(long *));
    C = (long **) malloc(matrix_size * sizeof(long *));
    D = (long **) malloc(matrix_size * sizeof(long *));

    for (i=0; i < matrix_size; i++) {
        A[i] = (long *) malloc(matrix_size * sizeof(long));
        B[i] = (long *) malloc(matrix_size * sizeof(long));
        C[i] = (long *) malloc(matrix_size * sizeof(long));
	D[i] = (long *) malloc(matrix_size * sizeof(long));
    }

    // Initialize with some values
    for (i=0; i < matrix_size; i++) {
        for (j=0; j < matrix_size; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
}

void multiply_matrix_parallel() {

    int i, j, k;

    #pragma omp parallel for  private(j, k)
    for (i=0; i < matrix_size; i++) {
        for (j=0; j < matrix_size; j++) {
            C[i][j] = 0;
            for (k=0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiply_matrix_serial() {

    int i, j, k;

    for (i=0; i < matrix_size; i++) {
        for (j=0; j < matrix_size; j++) {
            C[i][j] = 0;
            for (k=0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char const *argv[]) {

    matrix_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
	int i  ,j ;
    omp_set_num_threads(num_threads);
    allocate_matrix();

    double TP1 = omp_get_wtime();
    multiply_matrix_parallel();
    double TP2 = omp_get_wtime();

    double TS1 = omp_get_wtime();
    multiply_matrix_serial();
    double TS2 = omp_get_wtime();

    printf("Time Parallel Taken: %f ms\n", (TP2 - TP1) * 1000);
    printf("Time  Serial Taken: %f ms\n", (TS2 - TS1) * 1000);
    return 0;
}
