#include <iostream>
#include <vector>
//#include <omp.h>
#include <math.h>
#include <algorithm>
#include <unordered_set>



#define PROBLEM_SIZE 10

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
T *getInitialMeans(typename std::vector<T> data,int k) {
    T m[k];
    std::unordered_set<int> indexes;
    int i = 0
    while (i < k) {
       int index = rand() % (data.size() - 1);
       if (! indexes.find(index)){
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
    T old_means[k];
    T cluster_itrs[k];

 
    do {
    // saving old means
    for (int i = 0; i < k; i ++) {
        old_means[i] = means[i];
    }
    
 
    //creating clusters
    inp_itr=0;
    // cluster iterators
    int k_indexes[k] = {0};
    for( inp_itr=0; inp_itr<size; inp_itr++) {
        //calculating distance to means
        int min = INT32_MAX;
        int min_index = 0;
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
 
        t2=k0[inp_itr]-m2;
        if(t2<0){t2=-t2;}
 
        if(t1<t2) {
            //near to first mean
            k1[i2]=k0[inp_itr];
            i2++;
        }
        else {
            //near to second mean
            k2[i3]=k0[inp_itr];
            i3++;
        }
 
    }
 
    t2=0;
    //calculating new mean
    for(t1=0;t1<i2;t1++) {
        t2=t2+k1[t1];
    }
    m1=t2/i2;
 
    t2=0;
    for(t1=0;t1<i3;t1++) {
        t2=t2+k2[t1];
    }
    m2=t2/i3;
 
    //printing clusters
    cout<<"\nCluster 1:";
    for(t1=0;t1<i2;t1++) {
        cout<<k1[t1]<<" ";
    }
    cout<<"\nm1="<<m1;
 
    cout<<"\nCluster 2:";
    for(t1=0;t1<i3;t1++) {
        cout<<k2[t1]<<" ";
    }
    cout<<"\nm2="<<m2;
 
    cout<<"\n ----";
    
    } while(m1!=om1&&m2!=om2);
 
    cout<<"\n Clusters created";
 
    //ending
}



int main (int argc, char **argv) {
    auto x = getData<int>(3,58);
    int *t  = getInitialMeans<int>(x,3);

    //kmeans<int>(x);


    return 0;
}