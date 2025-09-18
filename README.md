# 2D Ising Model in C++

Generate simple 2D Ising Model data with perdiodic boundary conditions using the Metropolis algorithm in `C++`.

## Compiling

To compile the project simply use:

```bash
make
```

## Usage

To call the program from the terminal:

```bash
./exec L beta H N_cfg
```

Where:

* `int L` the size of the square lattice side
  in lattice units.
* `double beta` is the inverse temperature.
* `double H` is the external magnetic field.
* `int N_cfg` the number of configurations
  to generate.


