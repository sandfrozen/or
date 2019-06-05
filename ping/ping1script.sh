#! /bin/bash
#SBATCH -n 2
#SBATCH -e ping1-errors-%j.err
#SBATCH -o pingl-output-%j.out
echo 'AB enter'
mpiexec ./ping1 10000000000