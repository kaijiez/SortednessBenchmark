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
#include "../adaptive-radix-tree/include/art.hpp"
#include <cstdlib>
#include  <random>
#include  <iterator>
#include <ctime>

#include <chrono>
using namespace std;
using namespace std::chrono;


// completely sorted array
vector<int> sorted_array(int size){
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 0);

    return v;
}

//completely unsorted array
vector<int> unsorted_array(int size){
    std::vector<int> v(size);

    std::generate(v.begin(), v.end(), std::rand);

    return v;
}

// size : the length of our benchmark
// k: number of elements to be removed to keep array sorted
// l: the maximum distance between pair of inversions
vector<int> k_l_close_sorted(int size,int k, int l){
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 0);
    int distance = size/k;
    int count=0;
    int kcount=0;
    srand(time(NULL));  //initiazlie random number generator

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
    cout<<"here"<<endl;
    count=0;

    //generate elements for l
    for(int i=0;i<size;i++){
        if(count % distance!=0){
            int swappos = rand()%(l+1);
            if(i+swappos<size){
                if(issorted[i+swappos]==1 && issorted[i]==1){
                    swap(&v[i],&v[i+swappos]);
                    issorted[i+swappos]=0;
                    issorted[i]=0;
                }

            }
        }
        count+=1;

    }
    return v;
}

// check if input vector contain the values vector
bool rangeSearch(vector<int>input, vector<int>values){
    for(int x_v:values){

        bool found=false;
        for(int x_i:input ){
            
            if(x_i==x_v){
                found=true;
            }
        }
        if(found==false){
            return false;
        }
    }
    return true;
}

vector<std::tuple<int, int>> zoneMaps(vector<int> input){
    int size = input.size();
    std::vector<std::tuple<int, int>> v;
    int count=0;
    int start=0;
    for(int i=0;i<=size;i++){

        if(count%32000==0 && count!=0){
            v.push_back(std::make_tuple(*min_element(input.begin()+start, input.begin()+count), *max_element(input.begin()+start, input.begin()+count)));
            start=i;
        }
        
        count+=1;
    }

    return v;
}


bool linearSearch(vector<int> input, int value){
    for(int i: input){
        if(i==value){
            return true;
        }
    }
    return false;
}

void zoneMapRangeSearchTesting(vector<int> targets, vector<int>input){
    cout<<"measure zonemap performance on range reads"<<endl;
    vector<std::tuple<int, int>>zonemap= zoneMaps(input);
    int skipindex=0;
    vector<int> skipv;
    //get index from zonemaps
    std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
    for(int i=0;i<zonemap.size();i++){
        bool included=true;

        for(int rand: targets){
            // cout<<"rand "<<rand<<endl;
            if(rand<std::get<0>(zonemap[i]) || rand>std::get<1>(zonemap[i])){
                included=false;
                // cout<<"not included"<<endl;
                // cout<<"min zonemap"<<std::get<0>(zonemap[i])<<endl;
                // cout<<"max zonemap"<<std::get<1>(zonemap[i])<<endl;
                break;
            }
        
        }
        if(included)
            {
                // cout<<"min zonemap"<<std::get<0>(zonemap[i])<<endl;
                // cout<<"max zonemap"<<std::get<1>(zonemap[i])<<endl;
                skipindex=i*32000;
                if(std::find(skipv.begin(), skipv.end(), skipindex) != skipv.end()) {
                    
                }
                else{
                    skipv.push_back(skipindex);
                    // cout<<"inlude one: "<<skipindex<<endl;
                }
                
                
                
            }
    }

    //search for values

    for(int skipdistance:skipv){
       if(rangeSearch(std::vector<int>(input.begin()+skipdistance,input.begin()+skipdistance+32000),targets)==true){
        cout<<"zonemap found"<<endl;
        break;
        } 
    }
    std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " Microseconds" << std::endl;


    std::chrono::steady_clock::time_point begin4 = std::chrono::steady_clock::now();
    if(rangeSearch(input,targets)==true){
        cout<<"range search found"<<endl;
    }
    std::chrono::steady_clock::time_point end4 = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4).count() << " Microseconds" << std::endl;
}


void zoneMapLinearSearchTesting(int rand,vector<int> input){
    //zone maps testing on linear searching
    vector<std::tuple<int, int>>zonemap= zoneMaps(input);       //(min,max)
    int skipindex=0;
    vector<int> skipv;
    //get index from zonemaps
    std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
    for(int i=0;i<zonemap.size();i++){
        if(rand>=std::get<0>(zonemap[i]) && rand<=get<1>(zonemap[i])){
            skipindex=i*1000;
            skipv.push_back(skipindex);
        }
    }
    // std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();

    //search for values
    cout<<"skipindex "<<skipindex<<endl;
    for(int skipdistance:skipv){
       if(linearSearch(std::vector<int>(input.begin()+skipdistance,input.begin()+skipdistance+1000),rand)==true){
        cout<<"zonemap found"<<endl;
        break;
        } 
    }
    std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " Microseconds" << std::endl;


    std::chrono::steady_clock::time_point begin4 = std::chrono::steady_clock::now();
    if(linearSearch(input,rand)==true){
        cout<<"linear found"<<endl;
    }
    std::chrono::steady_clock::time_point end4 = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4).count() << " Microseconds" << std::endl;
    
}


//measure point read and insert latency for ART
void meansureARTperformance(vector<int> benchmark,int key){
    cout<<"the following is ART"<<endl;
    cout<<key<<endl;
    art1::art<int> m;

    for(int i:benchmark){
       m.set(std::to_string(i).c_str(),&i);
        
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int * v_ptr = m.get(std::to_string(key).c_str());

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " Nanoseconds" << std::endl;

}

//test insertion and Point read latency
void BTreePointRead(vector<int> input, int value){
    //BTree
    cout<<"\nThe following is BTree"<<endl;
    BTree t(3); // A B-Tree with minium degree 3

    // // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i: input){
        
        t.insert(i);
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if(t.search(value)){
        // cout << "Found\n";
    }
    else{
        // cout << "Not Found\n";
    }
 

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " Nanoseconds" << std::endl;
}

//test insertion and Point read latency
void TriePointRead(vector<int> input, int value){

    // //Our Trie implementation only take in values from 0 and forward

    
    // std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    cout<<"\nThe following is Trie"<<endl;
    struct TrieNode *root = getNode();
    for(int i:input){
         string num = to_string(i);
         Trie_insert(root,num);
    }
    
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    Trie_search(root, to_string(value))? cout << "Found\n" : cout << "Not Found\n"; 

    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " Microseconds" << std::endl;
   
}

//1st arg - size
//2nd arg - k
//3rd arg - l
int main(int argc, char** argv)
{   
    for (int i = 0; i < argc; ++i) {
        std::cout << i<<" "<<argv[i] << std::endl;
    }
    
    
    std::vector<int> v=k_l_close_sorted(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
    // std::vector<int> v= sorted_array(atoi(argv[1]));
    // std::vector<int> v= unsorted_array(atoi(argv[1]));

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
    // printArray(a,n);
    bubbleSort(a,n);
    cout<<"Sorted arrays: \n";
    // printArray(a, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" microseconds"<<endl;

    auto start2 = high_resolution_clock::now();
    int*a2 = &vcopy[0];
    cout<<"InsertionSort"<<endl;
    // printArray(a2,n);
    insertionSort(a2,n);
    cout<<"Sorted arrays: \n";
    // printArray(a2, n);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<duration2.count()<<" microseconds"<<endl;

    auto start3 = high_resolution_clock::now();
    int*a3 = &vcopy2[0];
    cout<<"QuickSort"<<endl;
    // printArray(a3,n);
    quickSort(a3,0,n-1);
    cout<<"Sorted arrays: \n";
    // printArray(a3,n);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout<<duration3.count()<<" Microseconds"<<endl;

    auto start4 = high_resolution_clock::now();
    int*a4 = &vcopy3[0];
    cout<<"Merge Sort"<<endl;
    // printArray(a4,n);
    mergeSort(a4,0,n-1);
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);
    cout<<duration4.count()<<" Microseconds"<<endl;

    auto start5 = high_resolution_clock::now();
    int*a5 = &vcopy4[0];
    cout<<"Heap Sort"<<endl;
    // printArray(a5,n);
    heapSort(a5,vcopy4.size());
    //cout<<"Sorted arrays: \n";
    //printArray(a3,n);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(stop5 - start5);
    cout<<duration5.count()<<" Microseconds"<<endl;

    // // cout<<"------------------"<<endl;
    srand(time(NULL));
    int rand = v[std::rand() % v.size()];
    cout<<"rand is:"<<rand<<endl;
    int min = *min_element(vcopy5.begin(), vcopy5.end());
    int max = *max_element(vcopy5.begin(), vcopy5.end());
    cout<<"num is: "<<min<<endl;
    
    zoneMapLinearSearchTesting(rand,vcopy5);


    int s=atoi(argv[1])*0.3;
    std::vector<int> targets(s);
    for(int i=0;i<s;i++){
        targets[i]=vcopy5[std::rand() % vcopy5.size()];
    }

    zoneMapRangeSearchTesting(targets,vcopy5);


    BTreePointRead(vcopy5,min);

    TriePointRead(vcopy5,rand);
    
    meansureARTperformance(vcopy5,min);

    return 0;
    }

