#include <vector>
#include <ctime>
#include <iostream>

int main() {
    const int n = 3000;
    std::vector<std::vector<double>> a(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> b(n, std::vector<double>(n, 1.0)); // Assuming filled with data
    std::vector<double> c(n, 1.0); // Assuming filled with data
    std::vector<double> c_inv(n);  // To store the inverse of c

    // Precompute the inverse of c[i]
    for (int i = 0; i < n; ++i) {
        c_inv[i] = 1.0 / c[i];
    }

    clock_t start = clock();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = b[i][j] * c_inv[i]; // Use multiplication instead of division
        }
    }
    clock_t end = clock();

    std::cout << "Optimized loop b time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds\n";

    return 0;
}

