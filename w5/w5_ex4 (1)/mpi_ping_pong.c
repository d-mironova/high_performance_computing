#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
    const int tag = 50;
    int id, ntasks, rc;
    MPI_Status status;
    int msg = 0;

    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS) {
        printf("MPI initialization failed\n");
        exit(1);
    }
    rc = MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (ntasks < 2) {
        printf("This program requires at least 2 processes\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(1);
    }

    if (id == 0) {
        // Process 0 sends the initial message to Process 1
        MPI_Send(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
        msg++;
        MPI_Send(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    } else if (id == 1) {
        // Process 1 receives, increments, and sends back the message
        MPI_Recv(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        msg++;
        MPI_Send(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        msg++;
        printf("Final value received by process 1: %d\n", msg);
        MPI_Send(&msg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

