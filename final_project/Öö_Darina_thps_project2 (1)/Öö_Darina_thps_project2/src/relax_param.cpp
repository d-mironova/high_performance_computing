#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <limits>

#define MAX_ITER 10000
#define TOL 1e-6

void initialize_grid(std::vector<std::vector<double>>& f, int N) {
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            if (i == 0 || i == N || j == 0 || j == N) {
                f[i][j] = sin(M_PI * i / N) * sin(M_PI * j / N);  // Example boundary condition
            } else {
                f[i][j] = 0.0;  // Initial guess
            }
        }
    }
}

double update_point(int i, int j, const std::vector<std::vector<double>>& f, const std::vector<std::vector<double>>& g, double gamma, int N) {
    double h2 = 1.0 / (N * N);
    return (1 - gamma) * f[i][j] + gamma / 4 * (f[i+1][j] + f[i-1][j] + f[i][j+1] + f[i][j-1]) - gamma * h2 * g[i][j] / 4;
}

int main() {
    int N = 100;  // Grid size
    double gamma_start = 1.0;
    double gamma_end = 2.0;
    double gamma_step = 0.05;
    std::vector<std::vector<double>> g(N + 1, std::vector<double>(N + 1, 1.0));  // Example g(x,y) = 1

    double optimal_gamma = gamma_start;
    int min_iterations = std::numeric_limits<int>::max();

    for (double gamma = gamma_start; gamma <= gamma_end; gamma += gamma_step) {
        std::vector<std::vector<double>> f(N + 1, std::vector<double>(N + 1));
        initialize_grid(f, N);

        bool converged = false;
        int iter = 0;
        while (!converged && iter < MAX_ITER) {
            converged = true;
            #pragma omp parallel for collapse(2)
            for (int i = 1; i < N; ++i) {
                for (int j = 1; j < N; ++j) {
                    if ((i + j) % 2 == 0) {  // Red points
                        double new_value = update_point(i, j, f, g, gamma, N);
                        if (std::abs(new_value - f[i][j]) > TOL) {
                            converged = false;
                        }
                        f[i][j] = new_value;
                    }
                }
            }
            #pragma omp parallel for collapse(2)
            for (int i = 1; i < N; ++i) {
                for (int j = 1; j < N; ++j) {
                    if ((i + j) % 2 == 1) {  // Black points
                        double new_value = update_point(i, j, f, g, gamma, N);
                        if (std::abs(new_value - f[i][j]) > TOL) {
                            converged = false;
                        }
                        f[i][j] = new_value;
                    }
                }
            }
            ++iter;
        }
        if (iter < min_iterations) {
            min_iterations = iter;
            optimal_gamma = gamma;
        }
        std::cout << "Gamma: " << gamma << " converged in " << iter << " iterations." << std::endl;
    }

    std::cout << "Optimal gamma: " << optimal_gamma << " with " << min_iterations << " iterations." << std::endl;
    return 0;
}

