#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_MESSAGES 100

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        int i;
        for (i = 1; i < size; i++) {
            int j;
            for (j = 0; j < NUM_MESSAGES; j++) {
                int message;
                MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Received message %d from process %d\n", message, status.MPI_SOURCE);
            }
        }
    } else {
        int i;
        for (i = 0; i < NUM_MESSAGES; i++) {
            int message = i;
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return 0;
}

