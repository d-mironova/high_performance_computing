#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <omp.h>

#define d 1.0
#define k1 1.0
#define k2 0.1
#define xsc 2.35

using namespace std;
using namespace std::chrono;

void accel(int nat, int i, double &u, double &a, double box, vector<double> &x) {
    int j, k;
    double dxl, dxr;

    j = i - 1;
    if (j < 0) j += nat;
    k = i + 1;
    if (k >= nat) k -= nat;

    dxl = x[i] - x[j] - d;
    dxr = x[k] - x[i] - d;

    // Apply periodic boundary conditions
    if (dxl < -box / 2.0) dxl += box;
    if (dxl > box / 2.0) dxl -= box;
    if (dxr < -box / 2.0) dxr += box;
    if (dxr > box / 2.0) dxr -= box;

    u = k1 * (dxl * dxl + dxr * dxr) / 2.0 + k2 * (dxl * dxl * dxl * dxr * dxr * dxr) / 2.0;
    a = -2.0 * k1 * (dxl - dxr) - 3.0 * k2 * (dxl * dxl - dxr * dxr) * (dxl + dxr);
}

int main(int argc, char **argv) {
    if (argc < 6) {
        cerr << "Usage: " << argv[0] << " <nat> <dt> <maxt> <vsc> <eout>\n";
        return 1;
    }

    int nat = atoi(argv[1]);
    double dt = atof(argv[2]);
    int maxt = atoi(argv[3]);
    double vsc = atof(argv[4]);
    int eout = atoi(argv[5]);

    double box = nat * d;
    vector<double> x(nat), v(nat), a(nat), ep(nat), ek(nat);

    unsigned int seed = time(nullptr);
    #pragma omp parallel for
    for (int i = 0; i < nat; ++i) {
        x[i] = i * d;
        seed = i; // Ensure different seed per thread
        double rn = static_cast<double>(rand_r(&seed)) / RAND_MAX;
        v[i] = vsc * (rn - 0.5);
    }

    auto start = high_resolution_clock::now();

    for (int t = 0; t < maxt; ++t) {
        #pragma omp parallel for
        for (int i = 0; i < nat; ++i) {
            double u;
            accel(nat, i, u, a[i], box, x);
            ep[i] = u;
        }

        #pragma omp parallel for
        for (int i = 0; i < nat; ++i) {
            v[i] += dt * a[i];
            x[i] += dt * v[i];
            // Apply periodic boundary conditions
            if (x[i] < 0) x[i] += box;
            if (x[i] >= box) x[i] -= box;
            ek[i] = 0.5 * v[i] * v[i];
        }

        if (t % eout == 0) {
            double total_epot = accumulate(ep.begin(), ep.end(), 0.0);
            double total_ekin = accumulate(ek.begin(), ek.end(), 0.0);
            cout << "Time: " << dt * t << " Total Energy: " << total_epot + total_ekin
                 << " Potential Energy: " << total_epot << " Kinetic Energy: " << total_ekin << endl;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    cout << "Simulation completed in " << static_cast<double>(duration) / 1e6 << " seconds\n";

    return 0;
}

