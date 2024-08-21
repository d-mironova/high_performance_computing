#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>

std::vector<float> readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::vector<float> data;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::copy(std::istream_iterator<float>(iss),
                  std::istream_iterator<float>(),
                  std::back_inserter(data));
    }

    return data;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::vector<float> data;
    if (world_rank == 0) {
        data = readFile("ex7p3.txt");
    }

    int dataSize = data.size();
    MPI_Bcast(&dataSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<int> sendCounts(world_size, dataSize / world_size);
    std::vector<int> displs(world_size, 0);

    // Handle the case where data size is not divisible by number of processes
    for (int i = 0; i < dataSize % world_size; ++i) {
        sendCounts[i]++;
    }
    std::partial_sum(sendCounts.begin(), sendCounts.end(), displs.begin() + 1);

    std::vector<float> localData(sendCounts[world_rank]);

    MPI_Scatterv(data.data(), sendCounts.data(), displs.data(), MPI_FLOAT,
                 localData.data(), sendCounts[world_rank], MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Calculate local sum and sum of squares
    float localSum = std::accumulate(localData.begin(), localData.end(), 0.0f);
    float localSqSum = std::inner_product(localData.begin(), localData.end(),
                                          localData.begin(), 0.0f);

    // Gather global sum and sum of squares
    float globalSum, globalSqSum;
    MPI_Reduce(&localSum, &globalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localSqSum, &globalSqSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calculate global mean and variance
    if (world_rank == 0) {
        float mean = globalSum / dataSize;
        float variance = (globalSqSum / dataSize) - (mean * mean);
        std::cout << "Mean: " << mean << ", Variance: " << variance << std::endl;
    }

    MPI_Finalize();
    return 0;
}

