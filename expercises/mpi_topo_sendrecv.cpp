#include <mpi.h>
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
    int ndims = 1,
        rc, 
        myid, 
        nprocs, 
        source, 
        dest, 
        dir, 
        shift,
        tag = 0;

    bool reorder = true;

    std::vector<int> dims(ndims),
                    coords(ndims);
    std::vector<int> periodic(ndims);

    MPI_Comm comm;
    MPI_Status status;

    rc = MPI_Init(&argc, &argv);
    {
        rc = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        rc = MPI_Comm_rank(MPI_COMM_WORLD, &myid);

        char msg_s = 'a'+myid;
        char msg_r;


        for ( int idx = 0 ; idx < ndims ; idx++ )
        {
            periodic[idx] = true;
            dims[idx] = 0;
        }

        rc = MPI_Dims_create(nprocs, ndims, &dims.front());
        rc = MPI_Cart_create(MPI_COMM_WORLD, ndims, &dims.front(), &periodic.front(), reorder, &comm);
        rc = MPI_Cart_coords(comm, myid, ndims, &coords.front());
        dir = 0;


        for ( int shift = -1 ; shift < 2 ; shift += 2 )
        {
            rc = MPI_Cart_shift(comm, dir, shift, &source, &dest);
            rc = MPI_Sendrecv(&msg_s, 1, MPI_CHAR, dest, tag, &msg_r, 1, MPI_CHAR, source, tag, comm, &status);

            
            std::cout << "sh\t" << shift << "\tid\t" << myid << "\tmsg_r\t" << msg_r << "\tsrc\t" << source << "\tdest\t" << dest << "\n";
        }


    }
    rc = MPI_Finalize();

    return 0;
}

