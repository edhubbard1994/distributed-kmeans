/**
 * Full parallelized version of the algorithm
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <unordered_set>



#define PROBLEM_SIZE 100000

using std::cin;
using std::cout;



template<typename T>
std::vector<T> getData(T lowest, T highest) {
    typename std::vector<T> data;
    data.resize(PROBLEM_SIZE);
    srand(time(NULL));
	for (auto index = data.begin(); index != data.end(); ++index) {
		*index = (rand() % highest) + lowest;
	}
    return data;
}

template<typename T>
bool compareArrays(T *arr1,T *arr2 ,int size) {
    #pragma omp parallel 
    for (int i = 0; i < size; i ++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
T *getInitialMeans(typename std::vector<T> data,int k) {
    T *m = (T *) calloc(k, sizeof(T));
    std::unordered_set<int> indexes;
    int i = 0;
    while (i < k) {
       int index = rand() % (data.size() - 1);
       if (indexes.find(index) == indexes.end()){
            m[i] = data[index];
            indexes.insert(index);
            ++i;
       }
    }
    return m;
}


template<typename T>
void kmeans(typename std::vector<T> data, int k) {
    int inp_itr,i2,i3,t1,t2;
    int size = data.size();
    T k0[size];
    std::copy(data.begin(), data.end(), k0);
    T clusters [k][size];
 
    T *means = getInitialMeans<T>(data, k);
    //old means
    T *old_means = (T *) calloc(k, sizeof(T));
    T *cluster_itrs = (T *) calloc(k, sizeof(T));
    bool checkMeans = compareArrays<T>(means, old_means, k);
 
    do {
    // saving old means
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
        #pragma omp parallel shared(min)
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
        int acc = 0;
        for(int j = 0; j < cluster_itrs[cluster]; j ++)  {
            acc += clusters[cluster][j];
        }
        means[cluster] = (acc / cluster_itrs[cluster]);
    }
    //printing clusters
    for (int cluster = 0; cluster < k; cluster ++) {
        cout<<"\nCluster " << cluster << ":\n" ;
        for(int x=0;x<cluster_itrs[cluster];x++) {
            cout<<clusters[cluster][x]<<" ";
        }
        cout<<"\nm" << cluster << "=" << means[cluster];
    }
    
    
 
    cout<<"\n ----";
    checkMeans = compareArrays<T>(means, old_means, k);
    } while( checkMeans == false);
 
    cout<<"\n Clusters created\n\n";
 
    //ending
    free(cluster_itrs);
    free(old_means);
    free(means);
}



int main (int argc, char **argv) {
    auto x = getData<int>(3,58);
    int *t  = getInitialMeans<int>(x,3);
    kmeans<int>(x,4);


    return 0;
}