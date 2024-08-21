#include <mpi.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <numeric>
#include <cstdlib>
#include <cmath>

#define d  1.0
#define k1 1.0
#define k2 0.1
#define xsc 2.35

using namespace std;
using namespace std::chrono; // Use the namespace for chrono

void accel(int nat, int i, double &u, double &a, double box, vector<double>& x) {
    int j, k;
    double dxl, dxr;
    
    j = i - 1; if (j < 0) j += nat;
    k = i + 1; if (k >= nat) k -= nat;
    
    dxl = x[i] - x[j];
    dxr = x[k] - x[i];
    
    // Apply periodic boundary conditions
    if (dxl < -box / 2.0) dxl += box;
    if (dxl > box / 2.0) dxl -= box;
    if (dxr < -box / 2.0) dxr += box;
    if (dxr > box / 2.0) dxr -= box;
    
    dxl -= d;
    dxr -= d;
    
    // Calculate potential energy and acceleration
    u = (k1 * (dxl * dxl + dxr * dxr) + k2 * (dxl * dxl * dxl * dxr * dxr * dxr)) / 2.0;
    a = -(2.0 * k1 * (dxl - dxr) + 3.0 * k2 * (dxl * dxl - dxr * dxr));
}

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Start timing from here for the master process
    auto start = high_resolution_clock::now();

    int nat, maxt, eout, coout;
    double dt, vsc, box;
    
    if (argc < 6) {
        if (rank == 0) {
            cerr << "Usage: mpirun -np <procs> " << argv[0] << " <nat> <dt> <maxt> <vsc> <eout> [coout]\n";
        }
        MPI_Finalize();
        return 1;
    }

    nat = atoi(argv[1]);
    dt = atof(argv[2]);
    maxt = atoi(argv[3]);
    vsc = atof(argv[4]);
    eout = atoi(argv[5]);
    coout = (argc > 6) ? atoi(argv[6]) : 0;

    int local_nat = nat / size;
    box = nat;
    
    vector<double> x(local_nat), v(local_nat), v0(local_nat), a(local_nat), ep(local_nat), ek(local_nat);
    double epsum, eksum, total_epot, total_ekin;

    // Initialize positions and velocities
    srand(time(NULL) + rank);
    for (int i = 0; i < local_nat; i++) {
        x[i] = i + rank * local_nat;
        double rn = static_cast<double>(rand()) / RAND_MAX;
        v[i] = vsc * (rn - 0.5);
    }

    for (int n = 0; n < maxt; n++) {
        for (int i = 0; i < local_nat; i++) {
            double u;
            accel(local_nat, i, u, a[i], box, x);
            ep[i] = u;
        }

        // Update positions and velocities (Leapfrog)
        for (int i = 0; i < local_nat; i++) {
            v[i] += dt * a[i];
            x[i] += dt * v[i];
            if (x[i] < 0) x[i] += box;
            if (x[i] >= box) x[i] -= box;
            double vave = (v0[i] + v[i]) / 2.0;
            ek[i] = 0.5 * vave * vave;
        }

        epsum = accumulate(ep.begin(), ep.end(), 0.0);
        eksum = accumulate(ek.begin(), ek.end(), 0.0);
        
        MPI_Reduce(&epsum, &total_epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&eksum, &total_ekin, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0 && (n % eout == 0)) {
            cout << dt * n << " " << total_epot + total_ekin << " " << total_epot << " " << total_ekin << endl;
        }
    }

    // Stop timing here for the master process
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // Print the wall clock time taken by the MPI program
    if (rank == 0) {
        cout << "Wall clock time taken: " << duration.count() / 1000000.0 << " seconds" << endl;
    }

    MPI_Finalize();
    return 0;
}

