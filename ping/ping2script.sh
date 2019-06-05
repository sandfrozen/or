#! /bin/bash
#SBATCH -n 2
#SBATCH -e ping2-errors-%j.err
#SBATCH -o ping2-output-%j.out
echo 'AB enter'
mpiexec ./ping2 10000000000