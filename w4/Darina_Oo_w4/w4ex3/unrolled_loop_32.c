#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 1000000

int main() {
    int array[ARRAY_SIZE];
    int sum = 0;

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    for (int i = 0; i < ARRAY_SIZE; i += 32) {
        sum += array[i];
        sum += array[i + 1];
        sum += array[i + 2];
        sum += array[i + 3];
        sum += array[i + 4];
        sum += array[i + 5];
        sum += array[i + 6];
        sum += array[i + 7];
        sum += array[i + 8];
        sum += array[i + 9];
        sum += array[i + 10];
        sum += array[i + 11];
        sum += array[i + 12];
        sum += array[i + 13];
        sum += array[i + 14];
        sum += array[i + 15];
        sum += array[i + 16];
        sum += array[i + 17];
        sum += array[i + 18];
        sum += array[i + 19];
        sum += array[i + 20];
        sum += array[i + 21];
        sum += array[i + 22];
        sum += array[i + 23];
        sum += array[i + 24];
        sum += array[i + 25];
        sum += array[i + 26];
        sum += array[i + 27];
        sum += array[i + 28];
        sum += array[i + 29];
        sum += array[i + 30];
        sum += array[i + 31];
    }

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Unrolling factor: 32\n");
    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}

