// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <mpi.h>
// #include <math.h>

// #define N 1e6

// int main (int argc, char* argv[])
// {
//     int rank, size, result = 0, sum = 0;
//     double e = 0.0
//     double begin=0.0, end=0.0
//     double x, y, y_p;
//     double y_max = 5.4365636;
    
//     MPI_Init (&argc, &argv);
    
//     // processor #
//     MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
//     // total processors
//     MPI_Comm_size (MPI_COMM_WORLD, &size);
    
//     // get the begin time
//     MPI_Barrier(MPI_COMM_WORLD);
//     begin = MPI_Wtime();
    
//     srand((int)time(0));
//     int total = 0;
    
//     // partial sum 
//     for (int i = rank; i < N; i += size)
//     {
//         x=rand()/(RAND_MAX+1.0);
//         y=rand()/(RAND_MAX+1.0) * y_max;
//         y_p = 2 * x * exp(x * x);
//         total++;
//         if(y <= y_p)
//             result++;
//     }
    
//     //Sum up all results
//     MPI_Reduce(&result, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
//     //Synchronize all processes and get the end time
//     MPI_Barrier(MPI_COMM_WORLD);
//     end = MPI_Wtime();
    
//     //Caculate and print PI
//     if (rank==0)
//     {
//         // pi=4*y_max*sum;
//         double e = ((double) result/ total) * y_max + 1;
//         printf("np=%2d;    Time=%fs;    PI=%0.4f\n", size, end-begin, e);
//     }
    
//     MPI_Finalize();
    
//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int size, my_rank;
    long long t = 1e8; 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long long local_t;
    long long count;
    long long local_count = 0;
    double x, y, z;
    double y_max = 5.4365636;
    double s_t = 0, e_t = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    s_t = MPI_Wtime();

    srand(time(NULL)); 

    if(my_rank == 0) {
        local_t = t / size;
    }

    MPI_Bcast(&local_t, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    for(long long i = 0; i < local_t; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX * y_max;
        z = 2 * x * exp(x * x);
        if(y <= z) {
            local_count++;
        }
    }

    MPI_Reduce(&local_count, &count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double e = y_max * (double)count / t + 1;
    double e_actual = exp(1);

    MPI_Barrier(MPI_COMM_WORLD);
    e_t = MPI_Wtime();

    if(my_rank == 0) {
        printf("# thread = %d\n", size);
        printf("# points = %lld\n", t);
        printf("calc e   = %f\n", e);
        printf("actual e = %f\n", e_actual);
        printf("time     = %f\n", e_t - s_t);
    }

    MPI_Finalize();
    return 0;
}
