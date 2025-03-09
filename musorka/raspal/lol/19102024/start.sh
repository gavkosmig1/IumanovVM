#!/bin/bash

#PBS -l walltime=00:018:00,nodes=3:ppn=2
#PBS -N job1
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 6 ./a.out
