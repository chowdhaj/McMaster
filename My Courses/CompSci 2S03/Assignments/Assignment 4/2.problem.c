// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// function prototypes
void printArray(int *arr, int size);
void generateMatrix(int *arr, int size);
void inputMatrix(int *arr, int size, int number);

// function prototype
int calculateUpperTriangularArea(int *arr, int size, int position);

int main() {

	int rowsColumns; // declare int variable // will hold number of rows/columns
	int matrix[25][25]; // declare a multi dimensional array // used to represent matrix

	printf("\nPlease Enter Number Of Rows OR Columns\n(Must Be Greater Than 1 & Less Than 26)\n==> "); // ask user to input size of matrix
	scanf("%d", &rowsColumns); // store input

	// this do block will check if input is less than 1 OR greater than 26
	do {
		if (rowsColumns < 1 || rowsColumns > 26) { // if input is less than 1 OR greater than 26
			printf("\nYour Input Must Be Greater Than 1 & Less Than 26\nPlease Try Again\n==> "); // prompt user to re-enter
			scanf("%d", &rowsColumns); // store input
		} else { // if user enters correct value, then:
			break; // break // used to exit loop
		}

	} while (1); // this loop will iterate until user enters a valid answer

	// size = number of numbers in the matrix
	// choice = binary number that will store decision
	// number = used to track index of matrix
	int size = rowsColumns * rowsColumns, choice, number = 1; // declare int variables

	printf("\nWould You Like To Generate %d Numbers Or Input Them?\n(0 = Generate | 1 = Input)\n==> ", size); // asks user if he wants to generate numbers or input them
    scanf("%d", &choice); // stores input
    
    if (choice == 1) { // if choice is 1, then input numbers
    	printf("\nPlease Enter %d Integers:\n", rowsColumns * rowsColumns); // tells user to enter X integers
    	
    	for (int i = 0; i < rowsColumns; i++) { // iterates through the multi-dimensional array
			inputMatrix(matrix[i], rowsColumns, number); // calls the inputMatrix function
			number += rowsColumns; // keeps track of what number user is at
		}

    } else if (choice == 0) { // if input is 0, then generate matrix
    	for (int i = 0; i < rowsColumns; i++) { // iterates through the multi-dimensional array
			generateMatrix(matrix[i], rowsColumns); // calls the generateMatrix function
		}
    } else { // else, exit program
    	puts("\n---------------------------------"); // prints divider
    	puts("ERROR: Not Valid. Exiting Program"); // prints error message
    	puts("---------------------------------\n"); // prints divider
    	exit(0); // exits program
    }

    puts(""); // prints newline

    // prints matrix to screen
	for (int i = 0; i < rowsColumns; i++) { // iterates through the multi-dimensional array
		printArray(matrix[i], rowsColumns); // prints i'th row of array
		if ( i != rowsColumns - 1) {
			puts("\n"); // prints newline after matrix line
		}
	}

	int position = rowsColumns - 1, area = 0; // declares int variables

	for (int i = 0; i < rowsColumns - 1; i++) { // iterates through the multi-dimensional array
		area += calculateUpperTriangularArea(matrix[i], rowsColumns, position); // calculates sum of each array
		position--; // decrements position
	}

	printf("\n\nThe Sum Of The Upper Triangular Area Is: %d\n\n", area); // prints out sum of upper triangular array

	return 0;

}

/*
 * this function calculates the upper trianglular area
 * accepts a single array, size of the array, and position
 */
int calculateUpperTriangularArea(int *arr, int size, int position) {

	int sum = 0; // declares and initializes sum to 0

	for(int i = size - 1; position > 0; position--, i--) { // iterates through single array
		sum += arr[i]; // adds elements to sum
	}

	return sum; // return sum
}

/*
 * this function allows user to input matrix value
 * accepts a single array, size of the array, and number of element
 */
void inputMatrix(int *arr, int size, int number) {

    for(int i = 0; i < size; i++) { // iterates through array
    	printf("%d. ", number++); // prints index of array
        scanf(" %d", &arr[i]); // stores input
    }
}

/*
 * this function generates a random matrix
 * accepts a single array and size
 */
void generateMatrix(int *arr, int size) {

	for(int i = 0; i < size; i++) { // iterates through array
		arr[i] = rand() % 9 + 1; // generates a random value and stores it
    }
}

/*
 * this function prints an array
 * accepts a single array and size
 */
void printArray(int *arr, int size) {

	for(int i = 0; i < size; i++) { // iterates through array
		printf("%d   ", arr[i]); // prints values
	}
}