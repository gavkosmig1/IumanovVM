#!/bin/bash

#PBS -l walltime=00:01:00,nodes=2:ppn=3
#PBS -N Program
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 6 ./a.out 1000
