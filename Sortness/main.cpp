#include <iostream>
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "BTree.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "Trie.h"
#include <chrono>
#include <vector>
#include <numeric>
#include <stdlib.h>
#include<string>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

//still in working progress

// size : the length of our benchmark
// k: number of elements to be removed to keep array sorted
// l: the maximum distance between pair of inversions
vector<int> k_l_close_sorted(int size,int k, int l){
    //cout<<"success"<<endl;
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 0);
    int distance = size/k;
    int count=0;
    int kcount=0;
    srand(time(NULL));

    //generate elements for k
    std::vector<int> issorted(size, 1);
    for(int i=0;i<size;i++){
        if(count % distance==0 && kcount<k){
            v[i] = (v[i]+1)*1000;
            issorted[i]=0;
            kcount+=1;
        }
        count+=1;
    }

    cout<<endl;
    count=0;

    //generate elements for l
    for(int i=0;i<size;i++){
        if(count % distance!=0){
            int swappos = rand()%(l+1);
            if(issorted[i+swappos]==1 && issorted[i]==1){
                swap(&v[i],&v[i+swappos]);
                issorted[i+swappos]=0;
                issorted[i]=0;

            }
        }
        count+=1;
    }

    return v;
}

template <typename I>
I random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);
    const unsigned long divisor = (RAND_MAX + 1) / n;

    unsigned long k;
    do { k = std::rand() / divisor; } while (k >= n);

    std::advance(begin, k);
    return begin;
}


int main()
{
    std::vector<int> v= k_l_close_sorted(15,7,3);
    // make copies of vector because sorting algorithms are in place
    std::vector<int> vcopy = v;
    std::vector<int> vcopy2 = v;
    std::vector<int> vcopy3 = v;
    std::vector<int> vcopy4 = v;
    std::vector<int> vcopy5 = v;
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
    int*a4 = &vcopy3[0];
    cout<<"Merge Sort"<<endl;
    printArray(a4,n);
    mergeSort(a4,0,n-1);
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout<<duration4.count()<<" Microseconds"<<endl;

    auto start5 = high_resolution_clock::now();
    int*a5 = &vcopy4[0];
    cout<<"Heap Sort"<<endl;
    printArray(a5,n);
    int nn = sizeof(a5) / sizeof(a5[0]);
    heapSort(a5,nn);
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    cout<<duration5.count()<<" Microseconds"<<endl;

    cout<<"------------------"<<endl;

    //int midindex = static_cast<int>(v.size())/2;
    int rand = *random_element(vcopy5.begin(), vcopy5.end());       //random number in input
    int min = *min_element(vcopy5.begin(), vcopy5.end());
    int max = *max_element(vcopy5.begin(), vcopy5.end());
    cout<<"max is: "<<max<<endl;

    //BTree
    auto start6 = high_resolution_clock::now();
    cout<<"\nThe following is BTree"<<endl;
    BTree t(3); // A B-Tree with minium degree 3
    for(int i: vcopy5){
        // cout<<"i= "<<i<<endl;
        t.insert(i);
    }
    if(t.search(max)){
        cout << "Found\n";
    }
    else{
        cout << "Not Found\n";
    }
    auto stop6 = high_resolution_clock::now();
    auto duration6 = duration_cast<microseconds>(stop6 - start6);
    cout<<duration6.count()<<" Microseconds"<<endl;

    //Our Trie implementation only take in values from 0 and forward
    auto start7 = high_resolution_clock::now();
    cout<<"\nThe following is Trie"<<endl;
    struct TrieNode *root = getNode();
    for(int i:vcopy5){
         string num = to_string(i);
         Trie_insert(root,num);
    }
    
    Trie_search(root, to_string(max))? cout << "Found\n" : cout << "Not Found\n"; 
    auto stop7 = high_resolution_clock::now();
    auto duration7 = duration_cast<microseconds>(stop7 - start7);
    cout<<duration7.count()<<" Microseconds"<<endl;

    return 0;
    }

