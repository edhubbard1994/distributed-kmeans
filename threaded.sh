make clean
make parallel
export OMP_NUM_THREADS=$1
make run_par
