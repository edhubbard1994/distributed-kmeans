CC=g++
CCFLAGS += -fopenmp
LIB += -g #-fopenmp

SERIAL_SRCS=main.cpp
PAR_SRCS=parallel.cpp
#HDRS= any h/hpp files


.PHONY:
bin:
	$(CC) $(LIB) $(SERIAL_SRCS) -o build/kmeans

.PHONY:
parallel:
	$(CC) $(CCFLAGS) $(LIB) $(PAR_SRCS) -o build/parallel_kmeans

.PHONY: both
both:
	$(CC) $(CCFLAGS) $(LIB) $(PAR_SRCS) $(SERIAL_SRCS) -D RUNNER -o build/both_kmeans

.PHONY:
run: 
	./build/kmeans

.PHONY:
run_par:
	./build/parallel_kmeans

.PHONY:
clean:
	rm -rf build/kmeans
	rm -rf build/parallel_kmeans
	rm -rf build/kmeans.dSYM
	rm -rf build/parallel_kmeans
	rm -rf build/both_kmeans
