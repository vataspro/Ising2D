#include "ising.h"


Ising2D::Ising2D(int size, double beta, double external_field) : 
                 lattice(size, std::vector<int>(size, 0)),
                 N(size),
                 b(beta),
                 H(external_field) {

    initialiseLattice();
    for (int k=0; k<THERMAL_ITERS; k++) {
        sweep();
    }
}


void Ising2D::initialiseLattice() {
        for (int i=0; i<N; i++) {
        ranlxs_fill_ising_vector(lattice[i]);
    }

}


void Ising2D::sweep() {

    for (int k=0; k<SWEEPS_PER_TRAJ; k++) {

        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                double energy = lattice[i][j] * 
                                    ( lattice[i][(j+1)%N]     +
                                        lattice[i][(N+j-1)%N] +
                                        lattice[(i+1)%N][j]   +
                                        lattice[(N+i-1)%N][j] );

                energy += H * lattice[i][j];

                if ((energy <= 0) || (ranlxs_rand() < exp(-2. * b  * energy)))
                    lattice[i][j] *= -1;
            }
        }
    }
}


double Ising2D::getMagnetisation() const {

    double s = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            s += lattice[i][j];
        }
    }

    return s / (N*N);
}


double Ising2D::getMagnetisationSquared() const {

    double s = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            s += lattice[i][j]*lattice[i][j];
        }
    }

    return s / (N*N);
}


int Ising2D::computeEnergy() const {
    int energy = 0;
    int Lx = lattice.size();          // number of rows
    int Ly = lattice[0].size();       // number of columns

    for (int i = 0; i < Lx; ++i) {
        for (int j = 0; j < Ly; ++j) {
            int s = lattice[i][j];
            // Periodic boundary conditions
            int right = lattice[i][(j + 1) % Ly];
            int down = lattice[(i + 1) % Lx][j];

            energy -= s * (right + down);
        }
    }

    return energy;
}


void Ising2D::print() const {

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            std::cout << std::setw(2) << std::setfill(' ') <<  lattice[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void Ising2D::save(std::string filename) const {

    std::ofstream out(filename);
    if (!out) {
        std::cerr << "error: failed to open file.\n";
        exit(1);
    }

    for (const auto row : lattice) {
        for (const auto elem : row) {
            out << elem << " ";
        }
        out << "\n";
    }

    out.close();
}
