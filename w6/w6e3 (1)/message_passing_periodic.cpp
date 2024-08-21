#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int id, ntasks;
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Status status;
    
    int message[1] = {id};
    // Determine the next process's ID with periodic boundary condition
    int next_id = (id + 1) % ntasks;
    
    // All processes send a message to the next process
    MPI_Send(message, 1, MPI_INT, next_id, 0, MPI_COMM_WORLD);
    std::cout << "Process " << id << " sent message to process " << next_id << std::endl;
    
    // Determine the previous process's ID with periodic boundary condition
    int prev_id = (id - 1 + ntasks) % ntasks;
    
    // All processes receive a message from the previous process
    MPI_Recv(message, 1, MPI_INT, prev_id, 0, MPI_COMM_WORLD, &status);
    std::cout << "Process " << id << " received message from process " << status.MPI_SOURCE 
              << " with content: " << message[0] << std::endl;

    MPI_Finalize();
    return 0;
}

