#!/ bin /bash -l
#SBATCH --nodes=1
#SBATCH --exclusive
#SBATCH --constraint=inca12
#SBATCH --account=kurse
echo "tsmm2:"
srun --export"=OMP_NUM_THREADS=1" -n 1 \
	/scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0 ./tsmm2
srun --export"=OMP_NUM_THREADS=2" -n 1 \
	/scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-1 ./tsmm2
srun --export"=OMP_NUM_THREADS=3" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-2 ./tsmm2
srun --export"=OMP_NUM_THREADS=4" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-3 ./tsmm2
srun --export"=OMP_NUM_THREADS=5" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-4 ./tsmm2
srun --export"=OMP_NUM_THREADS=6" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-5 ./tsmm2
srun --export"=OMP_NUM_THREADS=12" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-11 ./tsmm2

echo "tsmm8:"
srun --export"=OMP_NUM_THREADS=1" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0 ./tsmm4
srun --export"=OMP_NUM_THREADS=2" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-1 ./tsmm4
srun --export"=OMP_NUM_THREADS=3" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-2 ./tsmm4
srun --export"=OMP_NUM_THREADS=4" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-3 ./tsmm4
srun --export"=OMP_NUM_THREADS=5" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-4 ./tsmm4
srun --export"=OMP_NUM_THREADS=6" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-5 ./tsmm4
srun --export"=OMP_NUM_THREADS=12" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-11 ./tsmm4

echo "tsmm8:"
srun --export"=OMP_NUM_THREADS=1" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0 ./tsmm8
srun --export"=OMP_NUM_THREADS=2" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-1 ./tsmm8
srun --export"=OMP_NUM_THREADS=3" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-2 ./tsmm8
srun --export"=OMP_NUM_THREADS=4" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-3 ./tsmm8
srun --export"=OMP_NUM_THREADS=5" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-4 ./tsmm8
srun --export"=OMP_NUM_THREADS=6" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-5 ./tsmm8
srun --export"=OMP_NUM_THREADS=12" -n 1 \
        /scratch/performance_engineering_WS1819/likwid/bin/likwid-pin -c 0-11 ./tsmm8


