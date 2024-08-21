#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>

#define MAX_ITER 10000
#define TOL 1e-6

void initialize_grid(std::vector<std::vector<double>>& f, int N) {
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            f[i][j] = (i == 0 || i == N || j == 0 || j == N) ? 1.0 : 0.0;  // Example boundary conditions
        }
    }
}

double update_point(int i, int j, const std::vector<std::vector<double>>& f, double gamma, int N) {
    double h2 = 1.0 / (N * N);
    return (1 - gamma) * f[i][j] + gamma / 4 * (f[i+1][j] + f[i-1][j] + f[i][j+1] + f[i][j-1]) - gamma * h2 / 4;
}

int main() {
    int N = 100;  // Grid size
    double gamma = 1.95;  // Optimal over relaxation parameter
    int num_threads[] = {1, 2, 4, 8};  // Different number of threads to test scalability

    for (int t = 0; t < sizeof(num_threads) / sizeof(num_threads[0]); ++t) {
        omp_set_num_threads(num_threads[t]);
        std::vector<std::vector<double>> f(N + 1, std::vector<double>(N + 1));

        initialize_grid(f, N);

        auto start_time = std::chrono::high_resolution_clock::now();

        bool converged = false;
        int iter = 0;
        while (!converged && iter < MAX_ITER) {
            converged = true;
            #pragma omp parallel for collapse(2) reduction(&& : converged)
            for (int i = 1; i < N; ++i) {
                for (int j = 1; j < N; ++j) {
                    double new_value = update_point(i, j, f, gamma, N);
                    converged &= std::abs(new_value - f[i][j]) < TOL;
                    f[i][j] = new_value;
                }
            }
            ++iter;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;

        std::cout << "Threads: " << num_threads[t] << ", Time elapsed: " << elapsed.count() << "s, Iterations: " << iter << std::endl;
    }

    return 0;
}

