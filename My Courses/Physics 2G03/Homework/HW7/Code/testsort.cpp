#include <iostream>
#include <cstdlib>     
#include "sort.h"

int main() {
// A Program for testing sorting algorithms
// Filename: testsort.cpp Src: JWW 11/2020
 
  const int n = 10000;
  int i, isort;
  float A[n];

  for (i=0;i<n;i++) {
    A[i] = float(rand())/RAND_MAX;  // generate a random real number between 0 and 1
  }
  
  //for (i=0;i<n;i++) { std::cout << A[i] << ", "; }
  std::cout << " unsorted\n";

  std::cout << "Enter 1 for insertion sort, 2 for partition test, 3 for quick sort\n";
  std::cin >> isort;

  switch (isort) {
  case 1:
      InsertionSort( A, n );
      break;
  case 2:
      std::cout << "Count for small sub-array " << Partition( A, n ) << "\n";
      break;
  case 3:
      QuickSort(A,n);
      break;
  default:
    std::cout << isort << " is not an allowed choice\n";
  }

  //for (i=0;i<n;i++) { std::cout << A[i] << ", "; }
  
  std::cout << " sorted\n";
}
