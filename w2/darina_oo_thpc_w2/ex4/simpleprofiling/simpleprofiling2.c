#include <math.h>
#include <stdio.h>
#include <time.h>

// Define functions to isolate the loops
void loop1(long n) {
    double sum1 = 0.0;
    for (long i = 0; i < n; ++i) {
        sum1 += sin(i) * exp(i);
    }
    printf("Sum1: %e\n", sum1);
}

void loop2(long n) {
    double sum2 = 0.0;
    for (long i = 0; i < n; ++i) {
        sum2 += cos(i) * exp(i);
    }
    printf("Sum2: %e\n", sum2);
}

int main() {
    const long n = 1000000; // Adjust n as needed to increase computational load

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    loop1(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by loop1: %f\n", cpu_time_used);

    start = clock();
    loop2(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by loop2: %f\n", cpu_time_used);

    return 0;
}

