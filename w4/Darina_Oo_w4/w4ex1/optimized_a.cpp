#include <vector>
#include <ctime>
#include <iostream>

int main() {
    const int n = 10000000;
    std::vector<double> a(n, 0.0), b(n, 0.0);

    // Fill arrays a and b with data
    // ...

    clock_t start = clock();
    for (int i = 0; i < 500; ++i) {
        a[i] = 4.0 * b[i] + b[i + 1];
    }
    for (int i = 500; i < n - 1; ++i) {
        a[i] = 4.0 * b[i + 1] + b[i];
    }
    clock_t end = clock();

    std::cout << "Optimized loop time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds\n";

    return 0;
}

