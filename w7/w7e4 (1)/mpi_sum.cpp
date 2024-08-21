#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Ensure the number of processes is a power of two
    if ((world_size & (world_size - 1)) != 0) {
        std::cerr << "The number of processes must be a power of two." << std::endl;
        MPI_Finalize();
        return 1;
    }

    int sum = world_rank;
    int temp;

    for (int step = 1; step < world_size; step *= 2) {
        if ((world_rank & step) == 0) {
            if (world_rank + step < world_size) {
                MPI_Recv(&temp, 1, MPI_INT, world_rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sum += temp;
            }
        } else {
            MPI_Send(&sum, 1, MPI_INT, world_rank - step, 0, MPI_COMM_WORLD);
            break; // Once a process sends its sum, it is no longer involved in the algorithm
        }
    }

    if (world_rank == 0) {
        std::cout << "The sum of ranks is " << sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}

