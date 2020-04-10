#include <iostream>
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "BTree.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <stdlib.h>
//#include <windows.h>

using namespace std;
using namespace std::chrono;

//still in working progress
vector<int> k_l_close_sorted(int size,int k, int l){
    //cout<<"success"<<endl;
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 0);
    int distance = size/k+1;
    int count=0;
    srand(time(NULL));
    //int swapcount=rand()%l+1;
    //generate elements for k
    std::vector<int> issorted(size, 1);
    for(int i=0;i<size;i++){
        if(count % distance==0){
            v[i] = (v[i]+1)*1000;
            issorted[i]=0;
        }
        //cout<<v[i]<<",";
        count+=1;
    }

    cout<<endl;
    count=0;

    //generate elements for l
    for(int i=0;i<size;i++){
        if(count % distance!=0){
            int swappos = rand()%(l+1);
            //cout<<"index"<<i<<endl;
            //cout<<"swappos"<<swappos<<endl;
            if(issorted[i+swappos]==1 && issorted[i]==1){
                swap(&v[i],&v[i+swappos]);
                issorted[i+swappos]=0;
                issorted[i]=0;

            }
        }
        //cout<<v[i]<<endl;
        count+=1;
    }

    return v;
}

int main()
{
    std::vector<int> v= k_l_close_sorted(15,3,3);
    std::vector<int> vcopy = v;
    std::vector<int> vcopy2 = v;
    int n = v.size();
    auto start = high_resolution_clock::now();
    int* a = &v[0];
    cout<<"BubbleSort"<<endl;
    printArray(a,n);
    bubbleSort(a,n);
    cout<<"Sorted arrays: \n";
    printArray(a, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" microseconds"<<endl;

    auto start2 = high_resolution_clock::now();
    int*a2 = &vcopy[0];
    cout<<"InsertionSort"<<endl;
    printArray(a2,n);
    insertionSort(a2,n);
    cout<<"Sorted arrays: \n";
    printArray(a2, n);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<duration2.count()<<" microseconds"<<endl;


    //LARGE_INTEGER beginTime;
    //QueryPerformanceCounter( &beginTime );

    auto start3 = high_resolution_clock::now();
    int*a3 = &vcopy2[0];
    cout<<"QuickSort"<<endl;
    printArray(a3,n);
    quickSort(a3,0,n-1);
    cout<<"Sorted arrays: \n";
    printArray(a3,n);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout<<duration3.count()<<" Microseconds"<<endl;

    auto start4 = high_resolution_clock::now();
    int*a4 = &vcopy2[0];
    cout<<"Merge Sort"<<endl;
    printArray(a4,n);
    mergeSort(a4,0,n-1);
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout<<duration4.count()<<" Microseconds"<<endl;

    auto start5 = high_resolution_clock::now();
    int*a5 = &vcopy2[0];
    cout<<"Heap Sort"<<endl;
    printArray(a5,n);
    int nn = sizeof(a5) / sizeof(a5[0]);
    heapSort(a5,nn);
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    cout<<duration5.count()<<" Microseconds"<<endl;


    cout<<"The following is BTree"<<endl;
    BTree t(3); // A B-Tree with minium degree 3
    t.insert(1);
    t.traverse();

    return 0;
}
