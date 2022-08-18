// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h> 
#define SIZE 10

// function prototype
void printArray(int *arr, int size);

// function prototype
int getMax(int x1, int x2);
int getMaximum(int *arr, int len);

int main() {

	int numbers[SIZE] = {0,100,2,3,4,5,6,7,8,9}; // declares and initalizes an array

	printArray(numbers, SIZE); // prints the array

	printf("The Largest Number Is: %d\n\n", getMaximum(numbers, SIZE)); // prints the largest number in the array

	return 0;
}

// this function returns the maximum of the array using recursion
int getMaximum(int *arr, int len) {

	if (len == 1) { // if the length of the array is 1, then
		return arr[len-1]; // return the first element in the array
	} else {
		printf("");
		return getMax(getMaximum(arr, len - 1), arr[len -1]); // recursively calls 'getMaximum' until it gets the maximum
	}
}
/*

 getMaximum works like this:
 array = [1,2,3,4]
 getMax([1,2,3], 4)
 getMax([1,2], 3)
 getMax([1] 2)
 getMax([] 1)

 getMax 1, 2 --> 2
 getMax 2, 3 --> 3
 getMax 3, 4 --> 4

 return 4

 */

// this function gets the maximum of two numbers
int getMax(int x1, int x2) {

	if (x1 > x2) { // if x1 is larger than x2 then
		return x1; // return x1
	} else { // else
		return x2; // return x2
	}
}
 
// this function prints the array
void printArray(int *arr, int size) {

	puts("");
	for(int i = 0; i < size; i++) { // iterates through array
		printf("%d", arr[i]); // prints the element in the array
		if (i != 9) { 
			printf(", "); // prints commas after each number but NOT after the last one
		}
	}
	puts("\n"); // prints a newline
}