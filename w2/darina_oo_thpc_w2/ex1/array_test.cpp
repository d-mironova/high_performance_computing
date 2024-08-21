#include <iostream>
#include <exception>

int main() {
    int a[10];  // Array with 10 integers
    int i = 0;

    try {
        // Start accessing the array out of its bounds
        for (i = 10; ; ++i) {
            std::cout << "Accessing index " << i << ": ";
            a[i] = i;  // This is undefined behavior
            std::cout << a[i] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught at index " << i << ": " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught at index " << i << std::endl;
    }

    return 0;
}

