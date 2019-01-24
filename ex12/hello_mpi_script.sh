#!/ bin /bash -l
#SBATCH --time=1
#SBATCH --nodes=2
#SBATCH --exclusive
#SBATCH --constraint=inca12
#SBATCH --account=kurse

module load intelmpi


srun ./hello_mpi
