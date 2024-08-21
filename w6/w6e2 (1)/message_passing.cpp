#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int id, ntasks;
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (id < ntasks - 1) {
        // Sending process
        int message[1] = {id};
        MPI_Send(message, 1, MPI_INT, id + 1, 0, MPI_COMM_WORLD);
        std::cout << "Process " << id << " sent message to process " << id + 1 << std::endl;
    }
    
    if (id > 0) {
        // Receiving process
        int received_message[1];
        MPI_Status status;
        MPI_Recv(received_message, 1, MPI_INT, id - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << "Process " << id << " received message from process " << status.MPI_SOURCE 
                  << " with content: " << received_message[0] << std::endl;
    }

    MPI_Finalize();
    return 0;
}

