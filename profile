#!/bin/bash
make clean
make
cores=( 1 2 4 8 16 32 64 128 256)
for i in "${cores[@]}"
do
	export OMP_NUM_THREADS=$i
	echo "threads:  $i"
	./build/kmeans
done
