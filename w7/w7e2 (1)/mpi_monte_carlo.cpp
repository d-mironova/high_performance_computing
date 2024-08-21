#include <iostream>
#include <cmath>
#include <random>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int points_per_proc = 1000000;
    std::mt19937 rng(world_rank + time(NULL)); // Seed with different values for each process
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    int circle_count = 0;
    for (int i = 0; i < points_per_proc; ++i) {
        double x = dist(rng);
        double y = dist(rng);
        if (x*x + y*y <= 1.0) {
            ++circle_count;
        }
    }

    int total_circle_count;
    MPI_Reduce(&circle_count, &total_circle_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double pi_estimate = 4.0 * total_circle_count / (points_per_proc * world_size);
        std::cout << "Estimated Pi = " << pi_estimate << std::endl;
    }

    MPI_Finalize();
    return 0;
}

