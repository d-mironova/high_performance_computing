#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

int main() {
    clock_t t1, t2;
    struct timeval start, end;
    FILE *fp;
    const int iterations = 100000000; // Number of iterations for the loop
    double cpu_time_used, elapsed_time;
    int i;

    // Open a file for writing some output
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Get the start time for measuring wall-clock time
    gettimeofday(&start, NULL);

    // Begin measuring CPU time
    t1 = clock();

    // CPU-intensive task: Calculate sin(x) in a loop
    for (i = 0; i < iterations; i++) {
        fprintf(fp, "%f\n", sin(i));
    }

    // End measuring CPU time
    t2 = clock();

    // Get the end time for measuring wall-clock time
    gettimeofday(&end, NULL);

    // Calculate the CPU time used
    cpu_time_used = (double)(t2 - t1) / CLOCKS_PER_SEC;

    // Calculate elapsed time in microseconds and convert to seconds
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000;
    elapsed_time = (elapsed_time + (end.tv_usec - start.tv_usec)) / 1000000;

    // Close the file
    fclose(fp);

    // Print the CPU time and elapsed time
    printf("CPU Time Used: %f seconds\n", cpu_time_used);
    printf("Elapsed (Wall-Clock) Time: %f seconds\n", elapsed_time);

    return 0;
}

