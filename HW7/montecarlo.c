#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#define N 1e8

int main (int argc, char* argv[]) {
    int rank, size, result = 0, sum = 0;
    double e = 0.0;
    double begin=0.0, end=0.0; // time
    double x, y, y_p; // check particle
    double y_max = 5.4365636; // by 2 * 1 * exp(1*1)
    
    MPI_Init (&argc, &argv);
    
    // processor #
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    // total processors
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    // get the begin time
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();
    
    srand((int)time(NULL));
    int total = 0;
    
    // partial sum 
    for (int i = rank; i < N; i += size){
        // calculate point position
        x = rand() / (RAND_MAX + 1.0);
        y = rand() / (RAND_MAX + 1.0) * y_max;
        y_p = 2 * x * exp(x * x);
        total++;
        // under the curve 
        if(y <= y_p)
            result++;
    }
    
    // Sum up 
    MPI_Reduce(&result, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    
    // calculate e:
    if (rank==0){
        double e = ((double) result/ total) * y_max + 1;
        double e_true = exp(1);
        printf("number of threads: %d\n", size);
        printf("number of points: %.0f\n", N);
        printf("approximate e: %f\n", e);
        printf("theoretical e: %f\n", e_true);
        printf("running time: %f\n", end - begin);
    }
    
    MPI_Finalize();
    
    return 0;
}