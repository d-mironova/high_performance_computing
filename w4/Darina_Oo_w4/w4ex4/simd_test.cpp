#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

int main() {
    int n2 = 32; // Try varying this: 32, 64, 128, ..., 2560
    int n3 = 20000000;
    std::vector<int> d(n2, 5);
    std::vector<int> e(n2, 8); // 5 + 3
    std::vector<int> f(n2, 0);
    std::vector<double> times; // Store times for each run

    for (int run = 0; run < 10; ++run) { // Run multiple times
        clock_t start = clock();
        for (int i = 0; i < n3; ++i) {
            for (int j = 0; j < n2; ++j) {
                f[j] = d[j] * e[j];
            }
        }
        clock_t end = clock();
        double cpu_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        times.push_back(cpu_time);
        std::cout << "Run " << (run + 1) << " - Time: " << cpu_time << " seconds\n";
    }

    // Calculate average time and standard deviation
    double sum = 0.0, sq_sum = 0.0;
    for (double time : times) {
        sum += time;
        sq_sum += time * time;
    }
    double mean = sum / times.size();
    double variance = (sq_sum / times.size()) - (mean * mean);
    double stddev = std::sqrt(variance);

    std::cout << "Average Time: " << mean << " seconds\n";
    std::cout << "Standard Deviation: " << stddev << " seconds\n";

    return 0;
}

