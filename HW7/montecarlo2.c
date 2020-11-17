#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    long long N = atoi(argv[1]);
    int tn = atoi(argv[2]);


    // if(argc >= 2) {
    //     total = atoi(argv[1]);  
    // }
    // if(argc >= 3) {
    //     tn = atoi(argv[2]); 
    // }

    long count = 0;
    long total = 0;
    double x, y, y_check;
    double y_max = 5.4365636;

    #pragma omp parallel num_threads(tn)
    {
        unsigned seed = time(NULL);

        #pragma omp for private(x, y) reduction(+:count)

        for(long long i = 0; i < N; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX * y_max;
            y_check = 2 * x * exp(x * x);
            total++;
            
            if(y <= y_check) {
                count++;
            }
        }
    }

    double e_true = exp(1);
    double e = (double)count / total * y_max + 1;

    // printf("[+] total = %lld\n", total);
    // printf("[+] count = %lld\n", count);
    // printf("[+] e    = %f\n", e);
    // printf("num_threads = %d\n", tn);

    printf("number of threads: %d\n", tn);
    printf("number of points: %.0f\n", total);
    printf("approximate e: %f\n", e);
    printf("theoretical e: %f\n", e_true);
    return 0;
}