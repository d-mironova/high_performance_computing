#include <iostream>
#include <cmath>
#include <ctime>

template<typename T>
void compute_sum_and_time(long n) {
    T sum = 0;
    clock_t t1, t2;
    double cputime;

    t1 = clock();
    for (long k = 0; k <= n; ++k) {
        sum += exp(sin((T)k / 1000000));
    }
    t2 = clock();

    cputime = (double)(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "Sum using " << sizeof(T)*8 << "-bit floating point numbers: " << sum << std::endl;
    std::cout << "CPU time in seconds: " << cputime << std::endl;
}

int main() {
    long n = 100000000; // Example large value for n
    compute_sum_and_time<float>(n);    // 32-bit
    compute_sum_and_time<double>(n);   // 64-bit
    // For 128-bit, we assume a platform-specific 128-bit floating point type, like __float128
    // compute_sum_and_time<__float128>(n); // 128-bit (if available)

    return 0;
}

