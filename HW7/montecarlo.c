// This program is to caculate PI using MPI
// The algorithm is based on Monte Carlo method. The Monte Carlo method randomly picks up a large number of points in a square. It only counts the ratio of pints in side the circule.

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <mpi.h>
// #include <math.h>

// #define N 100000
// #define d 1E-8

// int main (int argc, char* argv[])
// {
//     int rank, size, error, i, result = 0, sum = 0;
//     double e = 0.0, begin=0.0, end=0.0, x, y, y_p;
//     double y_max = 5.4365636;
    
//     error = MPI_Init (&argc, &argv);
    
//     //Get process ID
//     MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
//     //Get processes Number
//     MPI_Comm_size (MPI_COMM_WORLD, &size);
    
//     //Synchronize all processes and get the begin time
//     MPI_Barrier(MPI_COMM_WORLD);
//     begin = MPI_Wtime();
    
//     srand((int)time(0));
//     int total = 0;
    
//     //Each process will caculate a part of the sum
//     for (i = rank; i < N; i += size)
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
    
//     error=MPI_Finalize();
    
//     return 0;
// }



//Monto Carlo algorithm

// #include<stdio.h>
// #include<mpi.h>
// #include<stdlib.h>
// #include<math.h>
// #define SEED 35467892 // TODO: make it rand

// int main(int argc, char* argv[]){ // TODO: make input
//     int rank , size; // rank is processor id, size is number of processors 
//     long niter = 10000000;   // total number of points used
//     double x , y , y_p;
//     int count = 0;
//     double y_max = 5.4365636;
//     double begin_time = 0.0;
//     double end_time = 0.0;
//     double sum = 0;

//     MPI_Init(&argc,&argv);
//     MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//     MPI_Comm_size(MPI_COMM_WORLD,&size);

//     MPI_Barrier(MPI_COMM_WORLD);
//     begin_time = MPI_Wtime();

//     int recieved[size];
//     int recvniter[size];
//     srand(SEED + rank);
//     if(rank != 0 ){
//         for(int i = 0; i < niter; i++ )
// 		{
//             x = ((double)rand())/RAND_MAX; 
//             y = ((double)rand())/RAND_MAX * y_max;  
//             y_p = 2 * x * exp(x * x);
//             if(y_p <= y)
//                 count++;
//         }
//         for(int j = 0; j < size; j++ )
// 		{
//             MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
//             MPI_Send(&niter,1,MPI_LONG,0,2,MPI_COMM_WORLD);
//         }
//     }
//     else if( rank == 0 ) 
// 	{
//         for(int i = 0; i < size; i++ )
// 		{
//             MPI_Recv(&recieved[i],size,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
//             MPI_Recv(&recvniter[i],size,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
//         }
//     }

//     //MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

//     MPI_Barrier(MPI_COMM_WORLD);
//     end_time = MPI_Wtime();

//     if( rank == 0 )
//     {
//         int finalcount = 0;
//         long finalniter = 0;

//         for(int i = 0; i < size; i++ ){
//             finalcount += recieved[i];
//             finalniter += recvniter[i];
//         }

//         double e = ((double) finalcount/(double) finalniter) * y_max + 1;
//         double accurate_e = exp(1);

//         printf("number of thread is: %d \n", size);
//         printf("number of particles is: %ld \n", niter);
//         printf("The approximate value of e is: %f \n",e);
//         printf("The actual value of e is: %f \n", accurate_e);
//         printf("The calculation time is: %f \n", end_time - begin_time);
//     }

//     MPI_Finalize();
// }




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int world_size, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    long long total;
    long long local_total;
    long long count;
    long long local_count = 0;
    double x, y, z;
    double y_max = 5.4365636;
    double s_t = 0, e_t = 0;

    MPI_Barrier(MPI_COMM_WORLD);
    s_t = MPI_Wtime();

    srand(time(NULL)); 

    if(my_rank == 0) {
        total = 1e6;  
        if(argc >= 2) {
            total = atoi(argv[1]);
        }
        local_total = total / world_size;
    }

    MPI_Bcast(&local_total, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    for(long long i = 0; i < local_total; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX * y_max;
        z = 2 * x * exp(x * x);
        if(y <= z) {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double e = y_max * (double)count / total + 1;
    double e_actual = exp(1);

    MPI_Barrier(MPI_COMM_WORLD);
    e_t = MPI_Wtime();

    if(my_rank == 0) {
        printf("# thread = %d\n", world_size);
        printf("# points = %lld\n", total);
        printf("e        = %f\n", e);
        printf("actual e = %f\n", e_actual);
        printf("time     = %f\n", e_t - s_t);
    }

    MPI_Finalize();
    return 0;
}
