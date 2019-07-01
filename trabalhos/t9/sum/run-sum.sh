#!/bin/bash
#SBATCH -J sum
#SBATCH -o sum.out
#SBATCH -e sum.err
#SBATCH --nodes 8
#SBATCH --ntasks-per-node 16
#SBATCH -p qCDER

module load Compilers/mvapich2_ACoRE

# compile the program
#mpicc sum.cpp -o sum
make

# execute any program
#to run MPI program
srun --mpi=pmi2 ./sum < sum.in
