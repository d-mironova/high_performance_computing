#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

int main() {
    const int size = 10000000;
    vector<float> a(size, 3.14); // Example array filled with the float value 3.14

    clock_t start, end;
    double cpu_time_used;

    // Unformatted write
    FILE *fu = fopen("unform.dat", "wb");
    start = clock();
    for (int i = 0; i < size; ++i) {
        fwrite((void *)&a[i], sizeof(a[i]), 1, fu);
    }
    end = clock();
    fclose(fu);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Unformatted write CPU time: " << cpu_time_used << " seconds" << endl;

    // Formatted write
    FILE *ff = fopen("form.dat", "w");
    start = clock();
    for (int i = 0; i < size; ++i) {
        fprintf(ff, "%g\n", a[i]);
    }
    end = clock();
    fclose(ff);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Formatted write CPU time: " << cpu_time_used << " seconds" << endl;

    return 0;
}

