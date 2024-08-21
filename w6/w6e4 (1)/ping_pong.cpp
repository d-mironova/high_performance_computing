#include <iostream>
#include <mpi.h>
#include <vector>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        if (rank == 0) {
            std::cerr << "This program requires at least two processes." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int num_rounds = 1000; // Number of ping-pongs
    for (int n = 1; n <= 1000000; n *= 10) { // Message sizes: 1B to 1MB
        std::vector<char> buffer(n);
        double start, stop, wallclock;

        MPI_Barrier(MPI_COMM_WORLD); // Ensure all processes start timing at the same point
        start = MPI_Wtime();

        for (int i = 0; i < num_rounds; ++i) {
            if (rank == 0) {
                MPI_Send(buffer.data(), n, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer.data(), n, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (rank == 1) {
                MPI_Recv(buffer.data(), n, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(buffer.data(), n, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            }
        }

        stop = MPI_Wtime();
        wallclock = stop - start;

        if (rank == 0) {
            double latency = wallclock / (2 * num_rounds) * 1e6; // microseconds
            double bandwidth = (n * num_rounds * 2 / wallclock) / (1 << 20); // MB/s
            std::cout << "Message size: " << n << " bytes, "
                      << "Latency: " << latency << " us, "
                      << "Bandwidth: " << bandwidth << " MB/s" << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}

