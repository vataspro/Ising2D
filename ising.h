/*
 *  C++ Implementation of the Ising Model
 */
#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "ranlxs.h"

// Number of thermalisation iterations
#define THERMAL_ITERS 100

// Number of sweeps per trajectory
#define SWEEPS_PER_TRAJ 10


/*
 *  2D Ising Model
 *    
 *    Assumes periodic boundary conditions -  
 *    the Ising Model lives on a torus.
 */
class Ising2D {

   public:
    int N; // Length of square lattice side
    double b; // Inverse temperature
    double H; // External field
    std::vector<std::vector<int>> lattice; // The spin values

    // Constructor
    Ising2D(int size, double beta, double external_field);

    // Single Metropolis sweep of the lattice
    void sweep();

    // Get the average magnetisation
    double getMagnetisation() const;

    // Get the average square magnetisation <m^2>
    double getMagnetisationSquared() const;

    // Compute the energy
    int computeEnergy() const;

    // Method to print the lattice
    void print() const;

    // Method to save the lattice to a txt file
    void save(std::string filename) const;

  private:
    // Method to iniatilise the lattice values
    void initialiseLattice();

};
