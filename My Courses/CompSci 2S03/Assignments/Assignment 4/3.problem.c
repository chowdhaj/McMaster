// Author: Jatin Chowdhary chowdhaj

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// function prototype
void printArray(int *arr, int size);
void randomizeArray(int *arr, int size);

int main() {

	int size = 10; // declares an int and initializes it to 10
	int numbers[10] = {0,1,2,3,4,5,6,7,8,9}; // declares and initializes an array

	puts("\nThe (Sorted) Array: "); // prints "sorted array"
	printArray(numbers, size); // prints the array

	randomizeArray(numbers, size); // randomizes the array by calling the 'randomizeArray' function

	puts("The Randomized Array"); // prints text
	printArray(numbers, size); // prints the array (randomized)
	puts(""); // prints a newline

	return 0; 
}

/* this function randomizes the items in the array
 * it does this by swapping the iterating through the array and swapping the i'th 
 *    element in the array, with a random element, generated using rand()
 * note: this is pseudo random
 */
void randomizeArray(int *arr, int size) {

	int r, temp; // declare two variables of type int
	srand(time(NULL)); // initialization of random // uses time

	for(int i = 0; i < size; i++) { // iterates through the array
		r = rand() % 9 + 1; // generates a random number between 1 to 9 and stores it in 'r'
		temp = arr[i]; // stores i'th element of array into 'temp'
		arr[i] = arr[r]; // swaps i'th element with r'th element
		arr[r] = temp; // r'th element gets 'temp'
	}
	puts(""); // prints newline
}

// this function prints the array
void printArray(int *arr, int size) {

	for(int i = 0; i < size; i++) { // iterates through array
		printf("%d", arr[i]); // prints the element in the array
		if (i != 9) { 
			printf(", "); // prints commas after each number but NOT after the last one
		}
	}
	puts(""); // prints a newline
}