#!/bin/sh

module load mpi/openmpi3-x86_64
mpicc gaussjordan_BROKEN.c -o gjBroken -lm
mpicc gaussjordan.c -o gj -lm
mpicc inverse.c -o inverse -lm
mpicc matrixmultiplyFix.c -o mmfix -lm
