/**
 * Full parallelized version of the algorithm
*/
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <exception>
#include <fstream>
#include <cstdlib>

#include "parallel.h"


//#define PROBLEM_SIZE 100000000

using std::cin;
using std::cout;

template<typename T>
std::vector<T> readData() {

	typename std::vector<T> data;
	std::ifstream input_file("data.txt");
	for( std::string line; getline( input_file, line ); )
	{	
		// std::cout << line << "\n";
		data.push_back( ((T) std::atoi(line.c_str())) );
	}
	return data;
}

template<typename T>
int kmeans(typename std::vector<T> data, int k, T* initial_means) {
    int inp_itr,i2,i3,t1,t2;
    int size = data.size();
    int iteration_count = 0;
    T k0[size];
    std::copy(data.begin(), data.end(), k0);
    T *means = (T*) calloc(k,sizeof(T));
    for (int i = 0; i < k; i ++) {
	means[i] = initial_means[i];
    }	
    T clusters [k][size];
    for (int i = 0; i < k; i ++) {
        for (int j = 0; j < size; j ++) {
            clusters [i][j] = 0;
        }
    }
    //old means
    T *old_means = (T *) calloc(k, sizeof(T));
    //bool checkMeans = compareArrays<T>(means, old_means, k);
    bool checkMeans = false;
     
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    do {
    // saving old means
    iteration_count ++;
    T *cluster_itrs = (T *) calloc(k, sizeof(T));
    for (int i = 0; i < k; i ++) {
        old_means[i] = means[i];
    }
    
 
    //creating clusters
    inp_itr=0;
    // cluster iterators
    for( inp_itr=0; inp_itr<size; inp_itr++) {
        //calculating distance to means
        int min = INT32_MAX;
        int min_index = 0;
        //#pragma omp parallel for //shared(min)
        for (int d_index = 0; d_index <  k; d_index ++) {
            int val = k0[inp_itr] - means[d_index];
            if (val < 0) {
                val = -val;
            }
            if (val < min) {
                min_index = d_index;
                min = val;
            }
        }
        clusters[min_index][cluster_itrs[min_index]] = k0[inp_itr];
	cluster_itrs[min_index] ++;
	
    }

    //calculating new means
    for(int cluster = 0; cluster < k; cluster ++) {
        T acc = 0;
        for(int j = 0; j < cluster_itrs[cluster]; j ++)  {
            acc += clusters[cluster][j];
        }
        means[cluster] = (acc / cluster_itrs[cluster]);
    }

    //printing clusters
    //for (int cluster = 0; cluster < k; cluster ++) {
      //  cout<<"\nCluster " << cluster << ":\n" ;
       // for(int x=0;x<cluster_itrs[cluster];x++) {
       //     cout<<clusters[cluster][x]<<" ";
       //  }
     //   cout<<"\nm" << cluster << "=" << means[cluster];
    //}
    
    
    free(cluster_itrs);
 
    //cout<<"\n ----";
    checkMeans = compareArrays<T>(means, old_means, k);
    } while( checkMeans == false);
 
    //cout<<"\n Clusters created\n\n";
 
    //ending
    free(old_means);
    free(means);
    // Print Time 
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //std::cout << "Average Time Elapsed Per Iteration: ";
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << (time / (1000.0 * iteration_count))  << ",";
    return iteration_count;
}



int main (int argc, char **argv) {
    auto x = readData<long>();
    long *t  = getInitialMeans< long>(x,3);
    int num_iterations = kmeans_parallel<long>(x,3,t); 
   
    return 0;
}
