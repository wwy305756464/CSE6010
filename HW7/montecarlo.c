#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    // define number of points and number of threads 
    long long N = atoi(argv[1]);
    int threads = atoi(argv[2]);

    // for summarize how many points under the curve
    long count = 0;
    double x, y, y_check;
    double y_max = 5.4365636;

    #pragma omp parallel num_threads(threads)
    {
        unsigned seed = time(NULL); // randome seed

        #pragma omp for private(x, y) reduction(+:count)

        // calculate whether the point under the curve or not
        for(long long i = 0; i < N; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX * y_max;
            y_check = 2 * x * exp(x * x);
            
            // if under the curve
            if(y <= y_check) {
                count++;
            }
        }
    }

    // calculate e
    double e_true = exp(1);
    double e = (double)count / N * y_max + 1;

    // print out
    printf("number of threads: %d\n", threads);
    printf("number of points: %d\n", N);
    printf("approximate e: %f\n", e);
    printf("theoretical e: %f\n", e_true);
    return 0;
}