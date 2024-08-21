#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

int main() {
    std::string line;
    std::vector<std::vector<double>> freqs;
    int coreCount = 0;

    // Reading each line of input
    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        double freq;
        int coreIndex = 0;
        while (iss >> freq) {
            if (freqs.size() <= coreIndex) {
                freqs.push_back(std::vector<double>());
            }
            freqs[coreIndex].push_back(freq);
            coreIndex++;
        }
        if (coreCount == 0) coreCount = coreIndex;
    }

    // Calculating averages and standard deviations
    for (int i = 0; i < coreCount; ++i) {
        double sum = 0.0, mean, standardDeviation = 0.0;
        for(double freq : freqs[i]) {
            sum += freq;
        }
        mean = sum / freqs[i].size();

        for(double freq : freqs[i]) {
            standardDeviation += pow(freq - mean, 2);
        }
        standardDeviation = sqrt(standardDeviation / freqs[i].size());

        std::cout << "Core " << i << ": Average Frequency = " << mean << " MHz, Standard Deviation = " << standardDeviation << " MHz" << std::endl;
    }

    return 0;
}

