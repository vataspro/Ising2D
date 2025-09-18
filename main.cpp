/*
 *  Run the Ising Model
 */

#include "ising.h"

constexpr double T_CRIT = 2.269185314213022; // Critical temperature
constexpr double BETA_CRIT = 1 / T_CRIT; // ~ 0.44


/*
 *  MAIN
 */
int main(int argc, char* argv[]) {

    // Guard
    if (argc != 5) {
        /*
         User should provide:
            - int N: lattice points in 1 dimension (N^2 points total)
            - float beta: the inverse temperature
            - float H: the external magnetic field
            - int N_cfg: number of sweeps (configurations to generate)
         */
        std::cerr << "Usage: " << argv[0] << " L beta H N_cfg\n";
        exit(1);
    }

    // Load command line arguments
    int N = atoi(argv[1]);
    double beta = atof(argv[2]);
    double H = atof(argv[3]);
    int N_cfg = atoi(argv[4]);

    // Initialise lattice
    Ising2D ising(N, beta, H);

    // Loop over trajectory generation
    for (int i=0; i < N_cfg; i++) {

        ising.sweep();
        double magnetisation = ising.getMagnetisation();
        double energy = ising.computeEnergy();

        std::cout << std::fixed << std::setprecision(15) << energy 
                  << " " <<  magnetisation << std::endl;
    }
    return 0;
}
