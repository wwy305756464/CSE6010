#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    long long total = 1e6;  // 默认100万个样本
    int tn = 2;             // 默认2个线程
    if(argc >= 2) {
        total = atoi(argv[1]);  // 从参数中获取样本数
    }
    if(argc >= 3) {
        tn = atoi(argv[2]);     // 从参数中获得线程数
    }

    long long count = 0;
    double x, y;
    #pragma omp parallel num_threads(tn)
    {
        unsigned seed = time(NULL);

        #pragma omp for private(x, y) reduction(+:count)
        for(long long i = 0; i < total; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if(x*x + y*y <= 1) {
                count++;
            }
        }
    }
    double pi = 4 * (double)count / total;

    printf("[+] total = %lld\n", total);
    printf("[+] count = %lld\n", count);
    printf("[+] pi    = %f\n", pi);
    printf("[+] loss  = %e\n", acos(-1) - pi);
    printf("\nnum_threads = %d\n", tn);

    return 0;
}