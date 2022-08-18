#include <iostream>
#include "sort.h"

void InsertionSort(float A[], int n) {
    std::cout << "Running Insertion Sort\n";
    
    float key = 0;
    int j = 0;
    
    for(int i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        
        while (j >= 0 && (A[j] > key)) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key; 
    }
}

int Partition(float A[], int n) {

    float swap1 = 0, swap2 = 0;
    float x = A[n - 1];
    int i = 0;
    
    for (int j = 0; (j < n - 2); j++) {
        if (A[j] <= x) {
            swap1 = A[i];
            A[i] = A[j];
            A[j] = swap1;
            i++;
        }
    }
    swap2 = A[i];
    A[i] = A[n-1];
    A[n-1] = swap2;
    
    return i;
}

void QuickSort(float A[], int n) {

    if (n > 1) {
        int q = Partition(A, n);
        QuickSort(A, q-1);
        QuickSort(A+q+1, n-1-q);
    }
}
