#!/bin/sh

module load mpi/openmpi3-x86_64
mpicc innerproduct.c -o inner -lm
mpicc innerproduct.c -o matrixaddsubtract -lm
mpicc matrixTranspose.c -o matrixtranspose -lm
mpicc matrixMultiply.c -o matrixmultiply -lm
