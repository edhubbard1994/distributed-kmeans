CC=g++

LIB += -g #-fopenmp

SRCS=main.cpp
#HDRS= any h/hpp files


.PHONY:
bin:
	$(CC) $(LIB) $(SRCS) -o build/kmeans

.PHONY:
run: 
	./build/kmeans

.PHONY:
clean:
	rm build/kmeans