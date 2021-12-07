CC=g++
LIB += -fopenmp
CCFLAGS += -g

SRCS=main.cpp
HEADERS=parallel.h


.PHONY:
bin:
	$(CC) $(LIB) $(CCFLAGS)  $(HEADERS)  $(SRCS) -o build/kmeans

.PHONY:
clean:
	rm -rf build/kmeans
	rm -rf build/parallel_kmeans
	rm -rf build/kmeans.dSYM
	rm -rf build/parallel_kmeans
	rm -rf build/both_kmeans
