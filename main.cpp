//
//  main.cpp
//  Heap
//
//  Created by 钟立 on 2016/11/15.
//  Copyright © 2016年 钟立. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstring>

#include "Heap.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SortTestHelper.h"


template <typename T>
void heapSort1(T arr[], int n) {
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for (int i = 0; i < n; i ++) {
        maxHeap.insert(arr[i]);
    }
    for (int i = n-1; i >= 0; i --) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void heapSort2(T arr[], int n){
    
    //heapify
    MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    for( int i = n-1 ; i >= 0 ; i-- )
        arr[i] = maxheap.extractMax();
    
}

template <typename T>
void __shiftDown(T arr[], int n, int k) {
    while (2*k+1 < n) {
        int i = 2*k+1;
        if (i+1 < n && arr[i+1] > arr[i]) {
            i += 1;
        }
        if (arr[i] > arr[k]) {
            swap(arr[k], arr[i]);
            k = i;
        } else {
            break;
        }
    }
}

//原地堆排序，相比前两个heapSort，不用开辟新空间，也少了一些赋值操作，因此速度更快
template <typename T>
void heapSort(T arr[], int n) {
    //现在堆是从0开始索引
    //heapify
    for (int i = (n - 1) / 2; i >= 0; i --) {
        __shiftDown(arr, n, i);
    }
    
    //每次将堆顶的最大的元素放到数组最后，再把剩余元素重新置换成最大堆
    for (int i = n - 1; i > 0; i --) {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}

int main(int argc, const char * argv[]) {
    
//    MaxHeap<int> maxHeap = MaxHeap<int>(100);
//    
//    srand((unsigned int)time(NULL));
//    for (int i = 0; i < 14; i ++) {
//        maxHeap.insert(rand() % 100);
//    }
//    
//    maxHeap.testPrint();
//    
//    maxHeap.extractMax();
//    
//    maxHeap.testPrint();
    
    int n = 1000000;
    
    // 测试1 一般性测试
    cout<<"Test for Random Array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);
    int* arr5 = SortTestHelper::copyIntArray(arr1, n);
    int* arr6 = SortTestHelper::copyIntArray(arr1, n);
    
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort", heapSort, arr6, n);
    
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    
    cout<<endl;
    
    
    // 测试2 测试近乎有序的数组
    int swapTimes = 100;
    cout<<"Test for Random Nearly Ordered Array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort", heapSort, arr6, n);
    
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    
    cout<<endl;
    
    
    // 测试3 测试存在包含大量相同元素的数组
    cout<<"Test for Random Array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n,0,10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);
    SortTestHelper::testSort("Heap Sort", heapSort, arr6, n);
    
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    
    
    return 0;
}
