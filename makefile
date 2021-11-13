CC=gcc

LIB += -fopenmp

SRCS=main.cpp
#HDRS= any h/hpp files


.PHONY:
bin:
	$(CC) $(LIB) $(SRCS) -o build/kmeans

.PHONY:
run: 
	./build/kmeans