#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

// Function to create CPU load
void createLoad() {
    volatile long long i;
    for(i = 0; i < 1000000000LL; ++i); // Simple loop for load
}

// Function to read CPU information
void readCpuInfo() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        // Look for lines containing 'processor' and 'BogoMIPS'
        if (line.find("processor") != std::string::npos ||
            line.find("BogoMIPS") != std::string::npos) {
            std::cout << line << std::endl;
        }
    }
}


int main() {
    // Start a thread to create CPU load
    std::thread loadThread(createLoad);

    // Read CPU information
    readCpuInfo();

    // Wait for the load thread to finish
    loadThread.join();

    return 0;
}

