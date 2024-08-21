#include <iostream>

int Ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    if (n == 0) {
        return Ackermann(m - 1, 1);
    }
    return Ackermann(m - 1, Ackermann(m, n - 1));
}

int main() {
    int m = 4;
    int n = 1;
    int result = Ackermann(m, n);
    std::cout << "Ackermann(" << m << ", " << n << ") = " << result << std::endl;
    return 0;
}

