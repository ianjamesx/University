#!/bin/bash

# File: mybash.sh

#SBATCH --job-name=myproject
#SBATCH --ntasks=30
#SBATCH --mem=2gb
#SBATCH --time=00:05:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/openmpi3-x86_64

# For a python3 project
# srun python3 ~/Projects/myproject/myproject.py

# For a C MPI project
mpirun ~/420/project/a.out
