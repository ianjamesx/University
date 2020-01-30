#!/bin/sh

module load mpi/openmpi3-x86_64
mpicc powermpi.c -o power
