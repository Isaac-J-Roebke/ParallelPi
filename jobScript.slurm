#!/bin/bash

#SBATCH --nodes=10
#SBATCH --ntasks=10
#SBATCH --time=0:10:00
#SBATCH --mail-type=END,FAIL
#SBATCH --account=PCS0268
#SBATCH --job-name=MPI_calcPI

module load mvapich2 
module load openmpi 
module load boost
# module load intelmpi

module load intel
cd $SLURM_SUBMIT_DIR/Default
make OSC
mpiexec -n 1 MPI >> results.csv
mpiexec -n 2 MPI >> results.csv
mpiexec -n 3 MPI >> results.csv
mpiexec -n 4 MPI >> results.csv
mpiexec -n 5 MPI >> results.csv
mpiexec -n 6 MPI >> results.csv
mpiexec -n 7 MPI >> results.csv
mpiexec -n 8 MPI >> results.csv
mpiexec -n 9 MPI >> results.csv
mpiexec -n 10 MPI >> results.csv
